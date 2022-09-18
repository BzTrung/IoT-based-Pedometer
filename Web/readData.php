<?php
header('Content-Type: application/json');

// dang nhap vao database
$server = "localhost";
    $user = "phuocphat"; 
    $pass = "26102001";
    $dbname = "pedometer";
    
    $conn = mysqli_connect($server,$user,$pass,$dbname);

// Doc gia tri RGB tu database
$sql = "select * from data where stt>(select max(stt) from data)-200";
$result = mysqli_query($conn,$sql);
/* $sql = "select step from data where stt=(select max(stt) from data)";
$result_1 = mysqli_query($conn,$sql);
$data2=$result_1; */
$data = array();
foreach ($result as $row){
    $data[] = $row;
}

mysqli_close($conn);
echo json_encode($data);
//echo $data2;

?>