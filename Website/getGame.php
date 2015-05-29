<!-- about.php
--	About page for game
--	December 8, 2014
-->

<?php
include_once("Includes/connectDB.php");

function printLinks($adf, $git){
    if(empty($adf) || empty($git)){
        echo "Unavailable";
    }else{
        echo '<a href="'.$adf.'">Adfly</a><br/>';
        echo '<a href="'.$git.'">Github</a>';
    }
}

function printDLRow($row){
    echo '<tr><td>'.$row['dtime'].'</td>';
    echo '<td>'.$row['version'].'</td>';
    echo '<td>';
    printLinks($row['adfly-bin'], $row['github-bin']);
    echo '</td><td>';
    printLinks($row['adfly-src'], $row['github-src']);
    echo "</td></tr>\n";
}
?>

<html>
<head>
	<title>Number Hunter Game</title>
	<LINK REL=StyleSheet HREF="/Style/MainStyle.css" TYPE="text/css" MEDIA=screen>
</head>

<body>
	<div id="page-container">
		<div id="header">
			<img src="Img/header.jpg" alt="header.jpg"/>
		</div><!-- close header -->
			
		<div id="navbar">
			<ul>
				<li><a href="/index.php">Home</a></li>
				<li><a href="/about.php">About</a></li>
				<li><a href="/getGame.php">Get The Game</a></li>
				<li><a href="/highscores.php?Level=1&diff=0">HighScores</a></li>
				<li class="last"><a href="/support.php">Support</a></li>
			</ul>
		</div><!-- close navbar -->
		
		<!-- Begin Main-Content -->
		<div id="main-content">
			<h1>Get The Game</h1>
			<p>This game is available as source code and a binary release. The source code
               may be found at <a href="http://adf.ly/wY8l7">http://adf.ly/wY8l7</a>.
               A binary release may be found at <a href="http://adf.ly/1FMxPi">
               http://adf.ly/1FMxPi</a>.</p>
			
			<!-- Available Downloads Table -->
			<h2>Available Downloads</h2>
			<table id="AvailDownloads">
				<tr>
					<th>Date</th>
					<th>Version</th>
                    <th>Binary</th>
                    <th>Source</th>
				</tr>
                <?php
                $sql = "SELECT * from Downloads ORDER BY id DESC;";
                $result = $dbConn->query($sql);
                foreach($result as $row){
                    printDLRow($row);
                }
                ?>
			</table>
		</div><!-- close main-content -->
		
		<?
			include("Includes/Footer.php");
		?>
	</div><!-- close page-container -->
</body>
</html>
