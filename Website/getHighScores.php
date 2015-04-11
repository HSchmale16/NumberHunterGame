<?php
// Gets the scores for a level from a mysql db for the client to display
include_once("Includes/connectDB.php");
$lvl = $_POST['Level'];
$diff = $_POST['diff'];

$tbName = getHiS_Tb_Name($lvl);
$sql = "Select NAME, SCORE from $tbName where DIFFICULTY=$diff order by SCORE DESC LIMIT 10;";
$result = $dbConn->query($sql);
if($result->num_rows > 0)
{
	while($row = $result->fetch_assoc())
	{
		echo $row["NAME"]." ".$row["SCORE"]." ";
	}
}
?>