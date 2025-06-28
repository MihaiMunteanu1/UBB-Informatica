<?php
$con = mysqli_connect("localhost:3307", "root", "", "labajax");
if (!$con) {
    die('Could not connect: ' . mysqli_error());
}


$result = mysqli_query($con, "SELECT DISTINCT memorie FROM produse");

$data = array();
while($row = mysqli_fetch_assoc($result)) {
    $data[] = $row['memorie'];
}

echo json_encode($data);

mysqli_close($con);
?>