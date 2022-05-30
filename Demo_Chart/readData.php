<?php
header('Content-Type: application/json');

// dang nhap vao database
include("config.php");

// Doc gia tri RGB tu database
$sql = "select * from chart where stt>(select max(stt) from chart)-20";
$result = mysqli_query($conn,$sql);

$data = array();
foreach ($result as $row){
   $data[] = $row;
}

// add random data
$d1 = rand(20, 50);
$d2 = rand(10, 60);
$d3 = rand(10, 60);

$sql = "insert into chart(data1,data2,data3) values ($d1,$d2,$d3)";
mysqli_query($conn,$sql);

mysqli_close($conn);
echo json_encode($data);

?>