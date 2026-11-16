<!-- 15.Develop a web application that accepts the user's name and age through an HTML form, stores the submitted information in a MySQL database table, and retrieves and displays all the existing records on the webpage using PHP -->
<?php
$conn = new mysqli("localhost", "root", "");
$conn->query("CREATE DATABASE IF NOT EXISTS mca2026");
$conn->select_db("mca2026");

$conn->query("CREATE TABLE IF NOT EXISTS person (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(100) NOT NULL, age INT NOT NULL)");

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $name = trim($_POST["name"] ?? "");
    $age = filter_var($_POST["age"] ?? "", FILTER_VALIDATE_INT);

    if ($name !== "" && $age !== false && $age >= 0) {
        $stmt = $conn->prepare("INSERT INTO person (name, age) VALUES (?, ?)");
        $stmt->bind_param("si", $name, $age);
        $stmt->execute();
        $stmt->close();
    } else {
        $message = "Please enter a valid name and age.";
    }
}

$result = $conn->query("SELECT name, age FROM person");
?>
<!DOCTYPE html>
<html>
<head>
    <title>Name and Age Records</title>
</head>
<body>
    <h1>Enter Your Name and Age</h1>
    <form method="post">
        <label>Name: <input type="text" name="name" required></label><br>
        <label>Age: <input type="number" name="age" min="0" required></label><br>
        <button type="submit">Save</button>
    </form>
    <?php if (isset($message)) { echo "<p>$message</p>"; } ?>

    <h2>All Records</h2>
    <table border="1">
        <tr><th>Name</th><th>Age</th></tr>
        <?php while ($row = $result->fetch_assoc()) { ?>
            <tr>
                <td><?= htmlspecialchars($row["name"]) ?></td>
                <td><?= htmlspecialchars($row["age"]) ?></td>
            </tr>
        <?php } ?>
    </table>
</body>
</html>
<?php $conn->close(); ?>
