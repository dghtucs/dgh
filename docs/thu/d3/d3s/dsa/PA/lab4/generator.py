import random
import sys

# 生成完全随机的操作序列，测试平均性能
def generate_random(n, max_val):
    ops = []
    present_keys = set()
    
    for _ in range(n):
        op_type = random.choice(['A', 'A', 'A', 'B', 'B', 'C', 'C'])
        
        if op_type == 'A':
            val = random.randint(0, max_val)
            while val in present_keys:
                val = random.randint(0, max_val)
            ops.append(f"A {val}")
            present_keys.add(val)
            
        elif op_type == 'B':
            if not present_keys:
                continue # Skip if empty
            val = random.choice(list(present_keys))
            ops.append(f"B {val}")
            present_keys.remove(val)
            
        elif op_type == 'C':
            val = random.randint(0, max_val)
            ops.append(f"C {val}")
            
    return ops

# 生成顺序插入和查询序列
def generate_sequential(n):
    ops = []
    # 顺序插入
    for i in range(n // 2):
        ops.append(f"A {i * 2}") # Gap for query
    
    # 顺序查询
    for i in range(n // 2):
        ops.append(f"C {i * 2 + 1}")
        
    return ops

# 生成具有局部性的数据
def generate_locality(n, max_val):
    ops = []
    present_keys = []
    
    # Initial population
    for i in range(100):
        val = random.randint(0, max_val)
        ops.append(f"A {val}")
        present_keys.append(val)
        
    for _ in range(n - 100):
        dice = random.random()
        
        # 80% 的概率操作 "热点" 数据 (最近操作过的附近)
        if dice < 0.8 and present_keys:
            target_idx = -1 # Last element
            center_val = present_keys[target_idx]
            # 生成一个在中心值附近的查询
            query_val = center_val + random.randint(-5, 5)
            ops.append(f"C {query_val}")
        else:
            # 20% 概率插入新值
            val = random.randint(0, max_val)
            ops.append(f"A {val}")
            present_keys.append(val)
            
    return ops

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python generator.py [mode] [n]")
        print("Modes: random, seq, locality")
        sys.exit(1)
        
    mode = sys.argv[1]
    n = int(sys.argv[2])
    max_val = 8500000
    
    result = []
    if mode == "random":
        result = generate_random(n, max_val)
    elif mode == "seq":
        result = generate_sequential(n)
    elif mode == "locality":
        result = generate_locality(n, max_val)
    else:
        print("Unknown mode")
        sys.exit(1)
        
    print(len(result))
    for line in result:
        print(line)