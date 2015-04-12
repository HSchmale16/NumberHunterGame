<?php
// Number Hunter Game HighScores Table Cleaning Script
// This script deletes the rows where the score is <= 0
// @date December 6, 2014

include_once("Includes/connectDB.php");

// iterate over Tables with highscores
for($level = 1; $level<=5; $level++){
	$tbName = getHiS_Tb_Name($level);
	$sql    = "DELETE FROM $tbName where SCORE <= 0;";
    $result = $dbConn->query($sql);
}
?>
