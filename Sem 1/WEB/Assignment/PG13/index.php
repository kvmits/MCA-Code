<html>
<head>
    <title>Electricity Bill Calculator</title>
</head>
<body>
    <h1>Electricity Bill Calculator</h1>
    <form method="get">
        <label for="units">Units used:</label>
        <input type="number" id="units" name="units" min="0" required>
        <button type="submit">Calculate bill</button>
    </form>
    <?php
    if (isset($_GET['units'])) {
        $units = filter_var($_GET['units'], FILTER_VALIDATE_INT);
        if ($units === false || $units < 0) {
            echo '<p>Enter a whole number of units that is zero or more.</p>';
        } elseif ($units <= 50) {
            $bill = $units * 3.50;
        } elseif ($units <= 150) {
            $bill = 50 * 3.50 + ($units - 50) * 4.00;
        } elseif ($units <= 250) {
            $bill = 50 * 3.50 + 100 * 4.00 + ($units - 150) * 5.20;
        } else {
            $bill = 50 * 3.50 + 100 * 4.00 + 100 * 5.20 + ($units - 250) * 6.50;
        }
        if ($units !== false && $units >= 0) {
            echo '<p>Bill for ' . $units . ' units: $' . number_format($bill, 2) . '</p>';
        }
    }
    ?>
</body>
</html>
