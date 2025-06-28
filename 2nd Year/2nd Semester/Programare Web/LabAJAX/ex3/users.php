<?php
$con = mysqli_connect("localhost:3307", "root", "", "labajax");
if (!$con) {
    die('Could not connect: ' . mysqli_error());
}

$result = mysqli_query($con, "SELECT * FROM users");

$users = array();
while ($row = mysqli_fetch_array($result)){
    $users[] = $row;
}

mysqli_close($con);

echo json_encode($users);
?>