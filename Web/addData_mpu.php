<?php
 // dang nhap vao database 
    $server = "localhost";
    $user = "phuocphat"; 
    $pass = "26102001";
    $dbname = "pedometer";
    
    $conn = mysqli_connect($server,$user,$pass,$dbname);
 
 // Check connection
    if($conn === false){
        die("ERROR: Could not connect. " . mysqli_connect_error());
    }
    $A=(float)$_POST["a_form"];
    $step=(int)$_POST["step_form"];
    $sql = "insert into data(A,step) values ($A,$step)";
    mysqli_query($conn,$sql);
    mysqli_close($conn);
?>