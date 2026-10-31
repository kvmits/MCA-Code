<?php

$conn = new mysqli("localhost", "root", "", "mca2026");
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "select * from student";

$result = $conn->query($sql);
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        echo $row["roll"] . $row["name"] . $row["age"] . "<br>";
    }
}

?>