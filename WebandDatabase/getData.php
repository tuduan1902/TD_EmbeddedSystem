<?php
// Send a JSON message to website
header('Content-Type: application/json');

// Connect to database
include("config.php");

// Read data from database
$sql = "select *from accounts"; // send data from database
$result = mysqli_query($conn, $sql);

// Send data to the website
$data = array();
foreach ($result as $row) {
   $data[]=$row;
} // read row by row of result variable
mysqli_close($conn);

echo json_encode($data);

?>