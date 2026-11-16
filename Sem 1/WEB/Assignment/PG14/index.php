<!-- 14.Create Database mca2026, and a table named student under the database. Implement all the DDL, SELECT commands and CRUD operations on the student table in MySQL. -->


<?php
$conn = mysqli_connect("localhost", "root", "", "mca2026");

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

$columns = mysqli_query($conn, "SHOW COLUMNS FROM student LIKE 'course'");

if (mysqli_num_rows($columns) == 0) {
    mysqli_query($conn, "ALTER TABLE student ADD course VARCHAR(50)");
}

mysqli_query($conn, "TRUNCATE TABLE student");

$primaryKey = mysqli_query($conn, "SHOW KEYS FROM student WHERE Key_name = 'PRIMARY'");

if (mysqli_num_rows($primaryKey) == 0) {
    mysqli_query($conn, "ALTER TABLE student MODIFY roll INT NOT NULL AUTO_INCREMENT, ADD PRIMARY KEY (roll)");
}

mysqli_query($conn, "INSERT INTO student (roll, name, age, course) VALUES (1, 'Amit', 20, 'MCA')");
mysqli_query($conn, "INSERT INTO student (roll, name, age, course) VALUES (2, 'Bina', 21, 'MCA')");

$result = mysqli_query($conn, "SELECT * FROM student");

while ($row = mysqli_fetch_assoc($result)) {
    echo $row['roll'] . " " . $row['name'] . " " . $row['age'] . " " . $row['course'] . "<br>";
}

mysqli_query($conn, "UPDATE student SET age = 22 WHERE name = 'Amit'");

mysqli_query($conn, "DELETE FROM student WHERE name = 'Bina'");

$result = mysqli_query($conn, "SELECT * FROM student");

while ($row = mysqli_fetch_assoc($result)) {
    echo "Updated: " . $row['roll'] . " " . $row['name'] . " " . $row['age'] . " " . $row['course'] . "<br>";
}

mysqli_close($conn);
?>
