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
	
	// escape the data fields to prevent sql injection
	$level = $dbConn->real_escape_string($level);
	$name = $dbConn->real_escape_string($name);
	$score = $dbConn->real_escape_string($score);
	$salvage = $dbConn->real_escape_string($salvage);
	$asteroids = $dbConn->real_escape_string($asteroids);
	$diff = $dbConn->real_escape_string($diff);
	
	if(($level > 0) and ($level <= 5))
	{
		// make sure table exists
		$tbName = getHiS_Tb_Name($level);
		$sql = "Create Table if not exists $tbName (ID INT PRIMARY KEY AUTO_INCREMENT,".
											        "DATE TIMESTAMP DEFAULT CURRENT_TIMESTAMP,".
													"NAME TEXT,".
													"SCORE INT,".
													"SALVAGE_COLLECTED INT,".
													"ASTEROIDS_DESTROYED INT,".
													"DIFFICULTY INT,".
                                                    "EnemiesKilled INT DEFAULT 0);";
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
