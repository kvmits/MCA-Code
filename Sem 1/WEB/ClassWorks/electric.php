<!-- first 50 units is 3.5/unit
for next 100 units is 4.0/unit
for next 100 units is 5.20/unit
for units above 250 is 6.50/units -->

<html>
<head>
    <title>Electricity Bill Calculator</title>
</head>
<body>
    <h1>Electricity Bill Calculator</h1>

    <form action="electric.php" method="get">
        <label for="units">Units used:</label>
        <input type="number" id="units" name="units" min="0" step="1" required value="<?= htmlspecialchars(is_string($_GET['units'] ?? null) ? $_GET['units'] : '', ENT_QUOTES, 'UTF-8') ?>">
        <button type="submit">Calculate bill</button>
    </form>

    <?php
    if ($_SERVER['REQUEST_METHOD'] === 'GET' && isset($_GET['units'])) {
        $units = filter_var(
            is_string($_GET['units'] ?? null) ? $_GET['units'] : null,
            FILTER_VALIDATE_INT
        );

        if ($units === false || $units < 0) {
            echo '<p>Please enter a whole number of units that is zero or more.</p>';
        } else {
            $bill = min($units, 50) * 3.50;

            if ($units > 50) {
                $bill += min($units - 50, 100) * 4.00;
            }
            if ($units > 150) {
                $bill += min($units - 150, 100) * 5.20;
            }
            if ($units > 250) {
                $bill += ($units - 250) * 6.50;
            }
            echo '<p>Electricity bill for ' . $units . ' units: $'
                . number_format($bill, 2) . '</p>';
        }
    }
    ?>
</body>
</html>
