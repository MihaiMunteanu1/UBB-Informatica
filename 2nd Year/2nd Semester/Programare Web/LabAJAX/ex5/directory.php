<?php

$path = 'C:\xampp\htdocs\LabAJAX\ex5';
$dir = new DirectoryIterator($path);
$childs = array();

foreach ($dir as $fileinfo) {
    if (!$fileinfo->isDot()) {
        array_push($childs, $fileinfo->getFilename());
    }
}
print json_encode($childs);
?>