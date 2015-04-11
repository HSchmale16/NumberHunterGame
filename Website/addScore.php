<!-- Database Submit Script
-->

<?php
	include_once("Includes/connectDB.php");
	
	$level = $_POST['level'];
	$name = $_POST['name'];
	$score = $_POST['score'];
	$salvage = $_POST['salvage'];
	$asteroids = $_POST['asteroids'];
	$diff = $_POST['diff'];
	
	if(($level > 0) and ($level <= 5))
	{
		// make sure table exists
		$tbName = getHiS_Tb_Name($level);
		$sql = "Create Table if not exists $tbName (ID INT PRIMARY KEY AUTO_INCREMENT,
													DATE TIMESTAMP,
													NAME TEXT,
													SCORE INT,
													SALVAGE_COLLECTED INT,
													ASTEROIDS_DESTROYED INT,
													DIFFICULTY INT);";
		if($dbConn->query($sql) === false)
		{
			die("Failed to create table" . $dbConn->error);		
		}
		
		// insert data
		$sql = "Insert into $tbName (NAME, SCORE, SALVAGE_COLLECTED, ASTEROIDS_DESTROYED, DIFFICULTY)
				Values ('$name' , $score, $salvage, $asteroids, $diff);";
		if($dbConn->query($sql) === false)
		{
			die("Failed to insert data: " . $dbConn->error);
		}
	}
?>
