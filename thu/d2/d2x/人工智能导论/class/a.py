def sorted_list(lst):
    """Sorts a list of integers in ascending order."""
    if not isinstance(lst, list):
        raise TypeError("Input must be a list")
    if not all(isinstance(i, int) for i in lst):
        raise TypeError("List must contain only integers")
    
    return sorted(lst)