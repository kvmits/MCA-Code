<!-- 16.Develop a web application using PHP and MySQL to perform the following operations:
	1. Create an HTML form to accept book details, including Book ID, Title, Author(s), Edition, and Publisher.
    2. Store the submitted book details in a MySQL database table.
	3. Implement a search functionality that accepts an author's name and retrieves all books associated with that author.
	4. Display the matching book records on the webpage. -->
<?php
$conn = new mysqli("localhost", "root", "", "", 3306);
$conn->query("CREATE DATABASE IF NOT EXISTS mca2026");
$conn->select_db("mca2026");
$conn->query("CREATE TABLE IF NOT EXISTS book (
    book_id INT PRIMARY KEY,
    title VARCHAR(100),
    authors VARCHAR(100),
    edition VARCHAR(50),
    publisher VARCHAR(100)
)");

$message = "";
$result = null;

if (isset($_POST["save"])) {
    $bookId = $_POST["book_id"];
    $title = $_POST["title"];
    $authors = $_POST["authors"];
    $edition = $_POST["edition"];
    $publisher = $_POST["publisher"];
    $stmt = $conn->prepare("INSERT INTO book (book_id, title, authors, edition, publisher) VALUES (?, ?, ?, ?, ?)");
    $stmt->bind_param("issss", $bookId, $title, $authors, $edition, $publisher);
    $stmt->execute();
    $stmt->close();
    $message = "Book saved.";
}

if (isset($_POST["search"])) {
    $author = "%" . $_POST["author"] . "%";
    $stmt = $conn->prepare("SELECT * FROM book WHERE authors LIKE ?");
    $stmt->bind_param("s", $author);
    $stmt->execute();
    $result = $stmt->get_result();
    $stmt->close();
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Book Records</title>
</head>
<body>
    <h1>Add a Book</h1>
    <form method="post">
        <label>Book ID: <input type="number" name="book_id" required></label><br>
        <label>Title: <input type="text" name="title" required></label><br>
        <label>Author(s): <input type="text" name="authors" required></label><br>
        <label>Edition: <input type="text" name="edition" required></label><br>
        <label>Publisher: <input type="text" name="publisher" required></label><br>
        <button type="submit" name="save">Save Book</button>
    </form>

    <p><?= htmlspecialchars($message) ?></p>

    <h2>Search by Author</h2>
    <form method="post">
        <label>Author's name: <input type="text" name="author" required></label>
        <button type="submit" name="search">Search</button>
    </form>

    <?php if ($result !== null) { ?>
        <h2>Matching Books</h2>
        <table border="1">
            <tr>
                <th>Book ID</th><th>Title</th><th>Author(s)</th><th>Edition</th><th>Publisher</th>
            </tr>
            <?php while ($row = $result->fetch_assoc()) { ?>
                <tr>
                    <td><?= htmlspecialchars($row["book_id"]) ?></td>
                    <td><?= htmlspecialchars($row["title"]) ?></td>
                    <td><?= htmlspecialchars($row["authors"]) ?></td>
                    <td><?= htmlspecialchars($row["edition"]) ?></td>
                    <td><?= htmlspecialchars($row["publisher"]) ?></td>
                </tr>
            <?php } ?>
        </table>
    <?php } ?>
</body>
</html>
<?php $conn->close(); ?>
