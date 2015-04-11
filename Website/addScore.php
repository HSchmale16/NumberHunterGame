<!-- Database Submit Script
-->

<?php
include_once("Includes/connectDB.php");	
if(($level > 0) and ($level <= 5))
{
    $level = $_POST['level'];
    $name = $_POST['name'];
    $score = $_POST['score'];
    $salvage = $_POST['salvage'];
    $asteroids = $_POST['asteroids'];
    $diff = $_POST['diff'];
    // make sure table exists
    $tbName = getHiS_Tb_Name($level);
    // insert data
    $sql = "Insert into $tbName (NAME, SCORE, SALVAGE_COLLECTED, ASTEROIDS_DESTROYED, DIFFICULTY)
        Values(:name , :score, :salvage, :asteroids, :diff);";
    try{
        $stmt = $dbConn->prepare($sql);
        $stmt->bindParam(':name', $name);
        $stmt->bindParam(':score', $score);
        $stmt->bindParam(':salvage', $salvage);
        $stmt->bindParam(':asteroids', $asteroids);
        $stmt->bindParam(':diff', $diff);

        $stmt->execute();
    }catch(PDOException $e){
        echo $e->getMessage();
    }
}else{
    error_log("Level Out of Bounds: ".$level);
}
?>
