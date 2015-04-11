<!-- highscores.php
--	Displays HighScores for game
--	December 8, 2014
-->

<?php
	include_once("Includes/connectDB.php");
?>


<html>
<head>
	<title>Number Hunter Game</title>
	<LINK REL=StyleSheet HREF="/Style/MainStyle.css" TYPE="text/css" MEDIA=screen>
</head>

<body>
	<div id="page-container">
		<div id="header">
			<img src="Img/header.jpg" alt="header.jpg">
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
			<?php
				$lvl = $_GET['Level'];
				$diff = $_GET['diff'];
				// heading
				echo "<h1>Global High Scores for Level $lvl on ";
				switch($diff){
					case 0:
						echo "Easy ";
						break;
					case 1:
						echo "Medium ";
						break;
					case 2:
						echo "Hard ";
						break;
				}
				echo "Difficuty</h1>";
				
				
			// LVL Selection
			echo "<ul class=\"minimenu\">";
				echo "<li><a href=\""."/highscores.php?Level=1&diff=$diff\">Level 1</a></li>";
				echo "<li><a href=\""."/highscores.php?Level=2&diff=$diff\">Level 2</a></li>";
				echo "<li><a href=\""."/highscores.php?Level=3&diff=$diff\">Level 3</a></li>";
				echo "<li><a href=\""."/highscores.php?Level=4&diff=$diff\">Level 4</a></li>";
				echo "<li><a href=\""."/highscores.php?Level=5&diff=$diff\">Level 5</a></li>";
			echo "</ul>";
			
			echo "<div style=\"clear:both;\"></div>";

			// Difficulty Selection
			echo "<ul class=\"minimenu\">";
				echo "<li><a href=\"highscores.php?Level=$lvl&diff=0\">EASY</a></li>";
				echo "<li><a href=\"highscores.php?Level=$lvl&diff=1\">MEDIUM</a></li>";
				echo "<li><a href=\"highscores.php?Level=$lvl&diff=2\">HARD</a></li>";
			echo "</ul>";
			?>
			<table id="Highscores">
				<tr>
					<td></td>
					<th>Date</th>
					<th>Name</th>
					<th>Score</th>
					<th>Salvage <br/> Collected</th>
					<th>Asteroids <br/> Destroyed</th>
				</tr>
				<?php
					// print high scores table from database
 					$tbName = getHiS_Tb_Name($lvl);
					$sql = "Select DATE, NAME, SCORE, SALVAGE_COLLECTED, ASTEROIDS_DESTROYED from $tbName where DIFFICULTY=$diff order by SCORE DESC LIMIT 100;";
					$result = $dbConn->query($sql);
					if($result->num_rows > 0) {
						$x = 1;
						while($row = $result->fetch_assoc()) {
							echo "<td class=\"RowNum\">".$x."</td><td>".$row["DATE"]."</td>";
							echo "<td>".$row["NAME"]."</td><td>".$row["SCORE"]."</td><td>".$row["SALVAGE_COLLECTED"];
							echo "</td><td>".$row["ASTEROIDS_DESTROYED"]."</td></tr>\n";
							$x = $x + 1;
						}
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