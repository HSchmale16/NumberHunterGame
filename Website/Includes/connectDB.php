<?php
// database connection script
// @note should be included on all pages that use the data base
// connects to the data base	and provides funtions to get the name of a table


$mysql_host = "mydb.db";
$mysql_database = "numhunter";
$mysql_user = "scoremanager";
$mysql_password = "47Ju822pmPqaGLjx";

$dbConn = new mysqli($mysql_host, $mysql_user, $mysql_password, $mysql_database);

if ($dbConn->connect_error) {
    die("Connection failed: " . $dbConn->error);
}

// gets the name of a highscore table
function getHiS_Tb_Name($level) {
    return "Lvl" . "$level" . "Scores";
}

// get the name of the table that holds game news
function getNews_Tb_Name() {
    return "GameNewsCDN";
}

// gets the name of the table that contains list of web admins
function getAdmin_Tb_Name() {
    return "Admins";
}
?>
