"""Conditional probability utilities."""

def conditional_probability(p_a_and_b: float, p_b: float) -> float:
    """Compute conditional probability P(A|B) = P(A and B) / P(B).

    Parameters
    - p_a_and_b: P(A and B), must be in [0,1]
    - p_b: P(B), must be > 0 and in (0,1]

    Returns
    - P(A|B) as a float in [0,1]
    """
    if p_b <= 0:
        raise ValueError("p_b must be > 0")
    if not (0 <= p_a_and_b <= 1):
        raise ValueError("p_a_and_b must be in [0,1]")
    res = p_a_and_b / p_b
    if not (0 <= res <= 1):
        raise ValueError("resulting conditional probability not in [0,1]; check inputs")
    return res


if __name__ == '__main__':
    # simple sanity checks
    examples = [
        (0.1, 0.5),  # P(A and B)=0.1, P(B)=0.5 -> P(A|B)=0.2
        (0.0, 0.3),  # zero joint
        (0.2, 0.4),  # 0.5
    ]
    for pa_pb, pb in examples:
        print(f"P(A and B)={pa_pb}, P(B)={pb} => P(A|B)={conditional_probability(pa_pb,pb):.6f}")


