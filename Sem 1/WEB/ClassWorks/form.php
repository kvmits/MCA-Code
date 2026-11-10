

<html>
    <body>
        <form action="form.php" method="post">
            <label for="name">Name:</label>
            <input type="text" id="name" name="name"><br><br>
            <input type="submit" value="Submit">
        </form>
    </body>

</html>

<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = $_POST["name"];
    echo "Hello, " . $name;
}