<?php
// database connection script
// @note should be included on all pages that use the data base
// connects to the data base	and provides funtions to get the name of a table


try{
    $dbConn = new PDO('sqlite:scores.sqlite');
}catch(PDOException $e){
    print 'Exception: '.$e->getMessage();
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
