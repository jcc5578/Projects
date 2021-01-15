<!-- Homepage -->

<!DOCTYPE html>
<html lang="en-US"> 
	
	<head>
		<meta charset="UTF-8">
		
		<link rel="stylesheet" href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css">
		<link rel="stylesheet" type="text/css" href="content/style.php" media="screen"></link>
		
		<center>
			<a href="index.html" rel="home">
			</a></center>
			
			<!--<body bgcolor = "#1DB954">style="font-size:0px"-->
			<center>
				<div class = buttonHolder>
					<a href="index.php"> <button class = "button currentButton">[Home]</button></a>
					<a href="recommender/index.php"> <button class = "button">[Music Recommender]</button></a>
					<a href="visual/index.php"> <button class = "button">[Taste Visualizer]</button></a>
					<a href="bands/index.php"> <button class = "button">[Nearby Bands]</button></a>
					<!--<a href="accom/index.html"> <button class = "button">[Accommodation]</button></a-->
				</div></center>
	</body>
	
	
</div></div>

<body>
	<header>
		
		<h3> Howdy! Welcome to our web app. We endeavor to help you find new music and learn about your own tastes.</h3>
		
	</header><!-- .page-header -->
	<hr>
	<img class="thumbnail2" src ="content/Logo.png" alt="Our logo" align="left" style="margin: 0px 10px 0px 0px;" />
	
	
	<div class="contact">
		<li><a href="recommender/index.php" style="color:black;font-size: 18px;">Let our web-app look through your most played artists and find similar artists that you haven't listened to.</a></li> <br>
		<li><a href="visual/index.php" style="color:black;font-size: 18px;">Explore your own tastes in music with graphs and statistics about your most played genres and artists.</a></li> <br>
		<li><a href="bands/index.php" style="color:black;font-size: 18px;">Find live music in your area that you are sure to love.</a></li> 
	</div> 
	
	<p class="tts-text" id="tts-text"> Hello there! Welcome to our web app! Please choose a tab from the top of the page. The order is Home, Recommender, Visualizer, Bands. </p>
	
	<script src="text2speech-test.js"></script>
	
</body>

<br style="clear:left;"/>
<hr>
<center>
	
	<?php
		
		if(!session_id()) {session_start();}
		else {
			$colorBlind = $_SESSION['colorBlind'];
			$poorSight = $_SESSION['poorSight'];
			setcookie("poorSight", $poorSight, time()+3600);
			setcookie("colorBlind", $colorBlind, time()+3600);
		}
		
		if (isset($_COOKIE["poorSight"])){
			$poorSight = $_COOKIE["poorSight"];
			$colorBlind = $_COOKIE["colorBlind"];
			} else if (!isset($poorSight)){
			$poorSight = "no";
			$colorBlind = "normal";
		}
		
		
		global $poorSight;
		global $colorBlind;
		
		if (isset($_POST["submit"])): 
		
		if ($_SERVER["REQUEST_METHOD"] == "POST") {
			if (isset($_POST["poorSight"])){
				$poorSight = $_POST["poorSight"];
				
			}
			if (isset($_POST["colorBlind"])){
				$colorBlind = $_POST["colorBlind"];
				
			}
			setcookie("poorSight", $poorSight, time()+3600);
			setcookie("colorBlind", $colorBlind, time()+3600);
		}
		
		endif;
		
		if(!session_id()){ 
			session_start();
		}
		$_SESSION['poorSight'] = $poorSight;
		$_SESSION['colorBlind'] = $colorBlind;
		
	?>
	<?php if($poorSight == "yes"){
		echo "<center><target=\"_blank\"> <button id = \"tts-button\" class = \"button\" style = \"width:100%\">Convert this page to audio</button></a></center>";
	}
	?> <br>
	<form action = # method = "POST">
		<label for="poorSight">Would you like your results converted to speech?: </label>
		<input type = "radio" name = "poorSight" value = "yes">Yes
		<input type = "radio" name = "poorSight" value = "no">No <br>
		
		<label for="colorBlind">How would you like your colors? : </label>
		<select id="colorBlind" name="colorBlind">
			<option value="normal">Normal</option>
			<option value="protanopia">Protanopia</option>
			<option value="deuteranopia">Deuteranopia</option>
			<option value="tritanopia">Tritanopia</option>
		</select> 
		<br>
		<input type="submit" class = "button" name="submit" value="Submit"/>
	</form>
	
	Current TTS: <?php echo $poorSight; ?> <br>
	Current Color Sight: <?php echo $colorBlind; ?>
</center>

</html>
