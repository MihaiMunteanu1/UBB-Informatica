<?php
$con = mysqli_connect("localhost:3307", "root", "", "labajax");
if (!$con) {
    die('Could not connect: ' . mysqli_error());
}

$result = mysqli_query($con, "SELECT distinct orasPlecare FROM trenuri");


while ($row = mysqli_fetch_array($result)) {
    echo "<option value=" . $row[0] . ">" . $row[0] . "</option>";
}
mysqli_close($con);
?>