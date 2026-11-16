<!-- 12.Build a PHP code to store students name and age in an associative array and display it using foreach loop. Sort and display the array using ksort, krsort, asort & arsort functions. -->
<?php
$students = [
    "Amit" => 20,
    "Bina" => 19,
    "Chetan" => 22
];

echo "Original array:<br>";
foreach ($students as $name => $age) {
    echo "$name => $age<br>";
}

ksort($students);
echo "<br>After ksort:<br>";
foreach ($students as $name => $age) {
    echo "$name => $age<br>";
}

krsort($students);
echo "<br>After krsort:<br>";
foreach ($students as $name => $age) {
    echo "$name => $age<br>";
}

asort($students);
echo "<br>After asort:<br>";
foreach ($students as $name => $age) {
    echo "$name => $age<br>";
}

arsort($students);
echo "<br>After arsort:<br>";
foreach ($students as $name => $age) {
    echo "$name => $age<br>";
}
?>

