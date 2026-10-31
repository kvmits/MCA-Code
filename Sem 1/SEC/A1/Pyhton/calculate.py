def process_order(items):
    """Calculate an order's financial breakdown.
    Args: items is a list of non-negative prices.
    Returns: A dictionary containing order totals.
    Raises: ValueError for empty orders or negative prices.
    """
    if not items:
        raise ValueError("Order cannot be empty")
    if any(price < 0 for price in items):
        raise ValueError("Item prices cannot be negative")
    subtotal = sum(items)
    if subtotal >= 100:
        discount = subtotal * 0.10
    else:
        discount = 0
    discounted_subtotal = subtotal - discount
    if discounted_subtotal >= 50:
        shipping = 0
    else:
        shipping = 10
    final_total = discounted_subtotal + shipping
    return {
        "subtotal": subtotal,
        "discount": discount,
        "discounted_subtotal": discounted_subtotal,
        "shipping": shipping,
        "final_total": final_total
    }
# Test cases
test_orders = [
    [40],
    [50],
    [100],
    [120],
    [],
    [-5]
]

for items in test_orders:
    try:
        result = process_order(items)
        print("\nOrder:", items)
        print("Subtotal:", result["subtotal"])
        print("Discount:", result["discount"])
        print("Discounted Subtotal:", result["discounted_subtotal"])
        print("Shipping:", result["shipping"])
        print("Final Total:", result["final_total"])

    except ValueError as error:
        print("\nInvalid Order:", error)