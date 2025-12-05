

### 1. 分支预测器 (Branch Predictor)
**文件**: branch_predictor.sv

这是一个基于 **BTB (Branch Target Buffer)** 和 **BHT (Branch History Table)** 的动态分支预测器。

*   **基本结构**:
    *   **BTB (分支目标缓冲)**: 一个直接映射 (Direct Mapped) 的表格，默认大小为 64 项。每一项存储了：
        *   `btb_tag`: 用于验证当前 PC 是否匹配该条目。
        *   `btb_target`: 预测的跳转目标地址。
        *   `btb_valid`: 该条目是否有效。
    *   **BHT (分支历史表)**: 与 BTB 对应的 2-bit 饱和计数器。
        *   `00`: 强不跳转 (Strongly Not Taken)
        *   `01`: 弱不跳转 (Weakly Not Taken)
        *   `10`: 弱跳转 (Weakly Taken)
        *   `11`: 强跳转 (Strongly Taken)

*   **预测逻辑 (IF 阶段)**:
    *   使用当前 PC 的一部分作为索引 (`index`) 查找 BTB。
    *   **命中条件**: `btb_valid[index]` 为真 且 `btb_tag[index]` 与当前 PC 的 Tag 匹配。
    *   **预测结果**: 如果命中，且 BHT 计数器的高位为 1 (即 `10` 或 `11`)，则预测跳转 (`pred_taken_o = 1`)，并将 `btb_target` 作为预测目标地址。

*   **更新逻辑 (EXE 阶段)**:
    *   当指令在 EXE 阶段被确认为分支或跳转指令时，更新预测器。
    *   **更新 BTB**: 无论是否跳转，都将当前指令的信息写入 BTB 对应位置（建立映射）。
    *   **更新 BHT**: 根据实际跳转结果 (`update_taken_i`) 更新饱和计数器。
        *   如果实际跳转了，计数器加 1 (上限 3)。
        *   如果实际没跳转，计数器减 1 (下限 0)。

### 2. 指令缓存 (ICache)
**文件**: icache.sv

这是一个 **直接映射 (Direct Mapped)**、**只读** 的缓存。

*   **参数**:
    *   `LINE_NUM`: 缓存行数，默认为 16 行。
    *   `DATA_WIDTH`: 数据宽度，32-bit (4字节)。
*   **存储结构**:
    *   `data_array`: 存储指令数据。
    *   `tag_array`: 存储地址 Tag。
    *   `valid_array`: 有效位。
*   **工作流程**:
    1.  **索引**: 用 PC 的中间位 (`index`) 选定一行。
    2.  **比对**: 检查 `valid_array` 是否有效，且 `tag_array` 是否与 PC 的高位匹配。
    3.  **Hit (命中)**: 直接在一个周期内返回 `data_array` 中的指令，置 `inst_valid_o = 1`。
    4.  **Miss (未命中)**:
        *   暂停流水线（不输出 valid）。
        *   通过 Wishbone 总线发起读请求 (`wbm_stb_o = 1`, `wbm_cyc_o = 1`)。
        *   等待总线应答 (`wbm_ack_i`)。
        *   收到数据后，写入 `data_array`，更新 `tag_array` 和 `valid_array`。
        *   返回数据。

### 3. 数据缓存 (DCache)
**文件**: dcache.sv

这是一个 **直接映射 (Direct Mapped)**、**写直通 (Write-Through)** 且 **写失效 (Write-Invalidate)** 的缓存。

*   **特殊机制**:
    *   **Uncached 区域**: 通过地址最高位判断 (`addr[31:28] != 0x8`)。如果地址不是 `0x8...` 开头（例如串口地址 `0x10000000`），则强制不经过缓存，直接访问总线。这对于 MMIO (内存映射 I/O) 至关重要。

*   **读操作 (Read)**:
    *   **Hit**: 如果命中且不是 Uncached 区域，直接返回数据。
    *   **Miss / Uncached**: 发起 Wishbone 总线读请求。
        *   收到数据后，如果是 Cached 区域（`0x8...`），则将数据填入缓存（Allocate）。
        *   如果是 Uncached 区域，则只返回数据，不填入缓存。

*   **写操作 (Write)**:
    *   采用 **写直通 (Write-Through)** 策略：所有写操作都直接发送到 Wishbone 总线，写入内存。
    *   **一致性维护 (Coherency)**: 采用简单的 **写失效 (Write-Invalidate)** 策略。
        *   如果写入的地址在缓存中命中（Hit），则将该行标记为无效 (`valid_array[index] <= 0`)。
        *   这样下次读取该地址时，必然会 Miss，从而从内存重新拉取最新数据。
        *   这种做法避免了复杂的脏位 (Dirty Bit) 和写回 (Write-Back) 逻辑，虽然写性能略低，但实现简单且安全。

### 总结
*   **分支预测**: 在循环和判断中减少流水线冲刷，显著提升 IPC (Instructions Per Cycle)。
*   **ICache**: 利用程序的时间局部性和空间局部性，极大减少了取指阶段对慢速内存的访问。
*   **DCache**: 加速了数据读取，并通过 Uncached 机制保证了 I/O 操作的正确性，通过写失效保证了数据一致性。
*   
