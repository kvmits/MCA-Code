<!-- 14.Create Database mca2026, and a table named student under the database. Implement all the DDL, SELECT commands and CRUD operations on the student table in MySQL. -->

<?php
$conn = new mysqli("localhost", "root", "", "");
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
$conn->query("CREATE DATABASE IF NOT EXISTS mca2026");
$conn->select_db("mca2026");

$sql = "CREATE TABLE IF NOT EXISTS student (roll INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(50), age INT, course VARCHAR(50))";
$conn->query($sql);
$columns = $conn->query("SHOW COLUMNS FROM student LIKE 'course'");
if ($columns->num_rows === 0) {
    $conn->query("ALTER TABLE student ADD course VARCHAR(50)");
}
$conn->query("TRUNCATE TABLE student");
$primaryKey = $conn->query("SHOW KEYS FROM student WHERE Key_name = 'PRIMARY'");
if ($primaryKey->num_rows === 0) {
    $conn->query("ALTER TABLE student MODIFY roll INT NOT NULL AUTO_INCREMENT, ADD PRIMARY KEY (roll)");
}
$conn->query("INSERT INTO student (roll, name, age, course) VALUES (1, 'Amit', 20, 'MCA')");
$conn->query("INSERT INTO student (roll, name, age, course) VALUES (2, 'Bina', 21, 'MCA')");

$result = $conn->query("SELECT * FROM student");
while ($row = $result->fetch_assoc()) {
    echo $row['roll'] . " " . $row['name'] . " " . $row['age'] . " " . $row['course'] . "<br>";
}

$conn->query("UPDATE student SET age = 22 WHERE name = 'Amit'");
$conn->query("DELETE FROM student WHERE name = 'Bina'");

$result = $conn->query("SELECT * FROM student");
while ($row = $result->fetch_assoc()) {
    echo "Updated: " . $row['roll'] . " " . $row['name'] . " " . $row['age'] . " " . $row['course'] . "<br>";
}
$conn->close();
?>