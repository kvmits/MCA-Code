<!-- 14.Create Database mca2026, and a table named student under the database. Implement all the DDL, SELECT commands and CRUD operations on the student table in MySQL. -->

<?php
$servername = "localhost";
$username = "root";
$password = "";
$conn = new mysqli($servername, $username, $password);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
$conn->query("CREATE DATABASE IF NOT EXISTS mca2026");
$conn->select_db("mca2026");

$sql = "CREATE TABLE IF NOT EXISTS student (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50),
    age INT,
    course VARCHAR(50)
)";
$conn->query($sql);
$conn->query("INSERT INTO student (name, age, course) VALUES ('Amit', 20, 'MCA')");
$conn->query("INSERT INTO student (name, age, course) VALUES ('Bina', 21, 'MCA')");

$result = $conn->query("SELECT * FROM student");
while ($row = $result->fetch_assoc()) {
    echo $row['id'] . " " . $row['name'] . " " . $row['age'] . " " . $row['course'] . "<br>";
}

$conn->query("UPDATE student SET age = 22 WHERE name = 'Amit'");
$conn->query("DELETE FROM student WHERE name = 'Bina'");

$result = $conn->query("SELECT * FROM student");
while ($row = $result->fetch_assoc()) {
    echo "Updated: " . $row['id'] . " " . $row['name'] . " " . $row['age'] . " " . $row['course'] . "<br>";
}
$conn->close();
?>