<!-- Homepage -->

<!DOCTYPE html>
<html lang="en-US"> 

<head>
<meta charset="UTF-8">

<!--<script src="bundle2.js"></script>-->
<!--<script src="app.js"></script>-->
<link rel="stylesheet" href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css">
<link rel="stylesheet" type="text/css" href="../content/style.php" media="screen"></link>
			
<center>
<a href="index.html" rel="home">
		</a></center>

<?php
	if (isset($_COOKIE["poorSight"])){
			$poorSight = $_COOKIE["poorSight"];
			$colorBlind = $_COOKIE["colorBlind"];
		} else if (!isset($poorSight)){
			$poorSight = "no";
			$colorBlind = "normal";
		}
	?>
<!--<body bgcolor = "#1DB954">style="font-size:0px"-->
<center>
<div class = buttonHolder>
<a href="../index.php"> <button class = "button">[Home]</button></a>
<a href="../recommender/index.php"> <button class = "button currentButton">[Music Recommender]</button></a>
<a href="../visual/index.php"> <button class = "button">[Taste Visualizer]</button></a>
<a href="../bands/index.php"> <button class = "button">[Nearby Bands]</button></a>
<!--<a href="accom/index.html"> <button class = "button">[Accommodation]</button></a-->
</div></center>
</body>


</div></div>


    <style type="text/css">
      #login, #loggedin {
        display: none;
      }
      .text-overflow {
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
        width: 500px;
      }
    </style>
  </head>

  <body>
    <div>
      <div id="login">
	  <center>
        <h3>Please login in order to allow our app to make recommendations.</h3>
		<p class = "tts-text" id = "tts-text"> </p>
        <button id="login-button" class="btn btn-primary">Log in with Spotify</button>
		</center>
      </div>
      <div id="loggedin">
        <div id="user-profile">
        </div>
		<div class = "recrow">
		<div class = "reccolumn">
		<div id="user-short-fav">
		</div>
		</div>
		<div class = "reccolumn">
		<div id="user-long-fav">
		</div>
		</div>
		</div>
		<div class = "recrow">
		<div class = "reccolumn">
		<div id="user-short-rec">
		</div>
		</div>
		<div class = "reccolumn">
		<div id="user-long-rec">
		</div>
		</div>
		</div>
        <div id="oauth">
        </div>
      </div>
    </div>
  </body>

    <script id="user-profile-template" type="text/x-handlebars-template">
	<body>
      <h1>Logged in as {{display_name}}</h1>
      <div class="media">
        <div class="pull-left">
          <img class="media-object" width="150" src="{{images.0.url}}" />
        </div>
        <div class="media-body">
          <dl class="dl-horizontal">
            <dt>Display name</dt><dd class="clearfix">{{display_name}}</dd>
            <dt>Id</dt><dd>{{id}}</dd>
            <dt>Email</dt><dd>{{email}}</dd>
            <dt>Spotify URI</dt><dd><a href="{{external_urls.spotify}}">{{external_urls.spotify}}</a></dd>
            <dt>Link</dt><dd><a href="{{href}}">{{href}}</a></dd>
            <!--<dt>Profile Image</dt><dd class="clearfix"><a href="{{images.0.url}}">{{images.0.url}}</a></dd>-->
            <dt>Country</dt><dd>{{country}}</dd>
          </dl>
        </div>
      </div>
	  <hr align = "left" style = "background-color:black;height:2px">
	  </body>
    </script>
	
	<script id="user-long-fav-template" type="text/x-handlebars-template">
	<body>
      <h1>Long Term</h1>
	  <p id = "tts-text" class = "tts-text"> Long Term Top Artists.</p>
      <div class="media">
        <!--<div class="pull-left">
          <img class="media-object" width="150" src="{{images.0.url}}" />
        </div>-->
		<div class="media-body">
		<b>Top Artists</b> <br>
		{{#each items}}
		 <b>{{@index}}.</b> {{this.name}} 
		 {{#each this.genres}}
			: {{this}}
			 {{/each}}
		 <br>
		 {{/each}}
		 </div>
      </div>
	  </body>
    </script>
	
	<script id="user-long-rec-template" type="text/x-handlebars-template">
	<body>
	<br>
      <b><h3>Recommendations</h3></b>
  
        <!--<div class="pull-left">
          <img class="media-object" width="150" src="{{images.0.url}}" />
        </div>-->
		<div class="media-body" width = "50%">
		{{#each tracks}}
		<hr align = "left">
		<div class = "music">
			<b><a href= "{{this.external_urls.spotify}}" target="_blank">{{this.name}}</a> 
		 {{#each this.artists}}
			: {{this.name}}
			 {{/each}}</b>
		 <br>
		 <img src ="{{this.album.images.[1].url}}">
		 <br>
		 <video controls src="{{this.preview_url}}autoplay=0&rel=0" width="300" height="80" frameborder="0" allowtransparency="true" allow="encrypted-media"></video>
		
		 </div>
		 {{/each}}
		 <hr align = "left" style = "background-color:black;height:2px">
		 </div>
	  </body>
    </script>
	
	<center>
	<script id="user-short-fav-template" type="text/x-handlebars-template">
	<body>
      <h1>Short Term</h1>
      <div class="media">
        <!--<div class="pull-left">
          <img class="media-object" width="150" src="{{images.0.url}}" />
        </div>-->
		<div class="media-body">
		<b>Top Artists</b> <br>
		{{#each items}}
		 <b>{{@index}}.</b> {{this.name}} 
		 {{#each this.genres}}
			: {{this}}
			 {{/each}}
		 <br>
		 {{/each}}
		 </div>
      </div>
	  </body>
    </script>
	
	<script id="user-short-rec-template" type="text/x-handlebars-template">
	<body>
	<br>
      <b><h3>Recommendations</h3></b>
  
        <!--<div class="pull-left">
          <img class="media-object" width="150" src="{{images.0.url}}" />
        </div>-->
		<div class="media-body" width = "50%">
		{{#each tracks}}
		<hr align = "left">
		<div class = "music">
		 <b><a href= "{{this.external_urls.spotify}}" target="_blank">{{this.name}}</a> 
		 {{#each this.artists}}
			: {{this.name}}
			 {{/each}}</b>
		 <br>
		 <img src ="{{this.album.images.[1].url}}">
		 <br>
		 <video controls src="{{this.preview_url}}autoplay=0&rel=0" width="300" height="80" frameborder="0" allowtransparency="true" allow="encrypted-media"></video>
		 </div>
		
		 
		 {{/each}}
		 <hr align = "left" style = "background-color:black;height:2px">
		 </div>
	  </body>
    </script>

    <script id="oauth-template" type="text/x-handlebars-template">
      <h2>oAuth info</h2>
      <dl class="dl-horizontal">
        <dt>Access token</dt><dd class="text-overflow">{{access_token}}</dd>
      </dl>
    </script>

    <script src="//cdnjs.cloudflare.com/ajax/libs/handlebars.js/2.0.0-alpha.1/handlebars.min.js"></script>
    <script src="http://code.jquery.com/jquery-1.10.1.min.js"></script>
    <script>
      (function() {

        var stateKey = 'spotify_auth_state';

        /**
         * Obtains parameters from the hash of the URL
         * @return Object
         */
        function getHashParams() {
          var hashParams = {};
          var e, r = /([^&;=]+)=?([^&;]*)/g,
              q = window.location.hash.substring(1);
          while ( e = r.exec(q)) {
             hashParams[e[1]] = decodeURIComponent(e[2]);
          }
          return hashParams;
        }
		
		function setCookie(cname, cvalue) {
		  var d = new Date();
		  d.setTime(d.getTime() + (60*60*1000));
		  var expires = "expires="+ d.toUTCString();
		  document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
		}
		
		function getCookie(cname) {
		  var name = cname + "=";
		  var decodedCookie = decodeURIComponent(document.cookie);
		  var ca = decodedCookie.split(';');
		  for(var i = 0; i <ca.length; i++) {
			var c = ca[i];
			while (c.charAt(0) == ' ') {
			  c = c.substring(1);
			}
			if (c.indexOf(name) == 0) {
			  return c.substring(name.length, c.length);
			}
		  }
		  return "";
		}
        /**
         * Generates a random string containing numbers and letters
         * @param  {number} length The length of the string
         * @return {string} The generated string
         */
        function generateRandomString(length) {
          var text = '';
          var possible = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';

          for (var i = 0; i < length; i++) {
            text += possible.charAt(Math.floor(Math.random() * possible.length));
          }
          return text;
        };

        var userProfileSource = document.getElementById('user-profile-template').innerHTML,
            userProfileTemplate = Handlebars.compile(userProfileSource),
            userProfilePlaceholder = document.getElementById('user-profile');
			
			userLongFavSource = document.getElementById('user-long-fav-template').innerHTML,
            userLongFavTemplate = Handlebars.compile(userLongFavSource),
            userLongFavPlaceholder = document.getElementById('user-long-fav');
			
			userLongRecSource = document.getElementById('user-long-rec-template').innerHTML,
            userLongRecTemplate = Handlebars.compile(userLongRecSource),
            userLongRecPlaceholder = document.getElementById('user-long-rec');
			
			userShortFavSource = document.getElementById('user-short-fav-template').innerHTML,
            userShortFavTemplate = Handlebars.compile(userShortFavSource),
            userShortFavPlaceholder = document.getElementById('user-short-fav');
			
			userShortRecSource = document.getElementById('user-short-rec-template').innerHTML,
            userShortRecTemplate = Handlebars.compile(userShortRecSource),
            userShortRecPlaceholder = document.getElementById('user-short-rec');

            oauthSource = document.getElementById('oauth-template').innerHTML,
            oauthTemplate = Handlebars.compile(oauthSource),
            oauthPlaceholder = document.getElementById('oauth');

        var params = getHashParams();
		
		

        var access_token = params.access_token,
            state = params.state,
            storedState = localStorage.getItem(stateKey);
			
			if (access_token) {
				setCookie("token", access_token);
			} else {
				access_token = getCookie("token");
			}
			
			
        /*if (access_token && (state == null || state !== storedState)) {
          alert('There was an error during the authentication');
        }*/
          localStorage.removeItem(stateKey);
          if (access_token != "") {
			$.ajax({
                url: 'https://api.spotify.com/v1/me',
                headers: {
                  'Authorization': 'Bearer ' + access_token
                },
                success: function(response) {
                  userProfilePlaceholder.innerHTML = userProfileTemplate(response);

                  $('#login').hide();
                  $('#loggedin').show();
                }
            });
			
			var longResponse;
			var shortResponse;
			
			$.ajax({
                url: 'https://api.spotify.com/v1/me/top/artists',
                headers: {
                  'Authorization': 'Bearer ' + access_token
                },
				data: {"limit": "10","time_range":"long_term"},
				offset: 0,
				time_range:'long_term',
				json: true,
                success: function(response) {
				  longResponse = response;
                  $('#login').hide();
                  $('#loggedin').show();
				  if (response.items.length > 0){
				    userLongFavPlaceholder.innerHTML = userLongFavTemplate(response);
					console.log(longResponse);
					var artists = 5
					if (response.items.length < 5) {
						artists = response.items.length;
					}
					var i;
					var artistList = response.items[0].id;
					var artistNameList = response.items[0].name;
					for (i = 1; i < artists; i++){
						artistList += "," + response.items[i].id;
						artistNameList += ", " + response.items[i].name;
					}
					document.getElementById("tts-text").innerHTML += "Your Top Long Term artists are: " + artistNameList + "\n ";
					console.log(artistList);
					$.ajax({
						url: 'https://api.spotify.com/v1/recommendations',
						headers: {
						  'Authorization': 'Bearer ' + access_token
						},
						data: {"seed_artists": artistList,"min_popularity": "50", "limit" : "10"},
						json: true,
						success: function(recResponse) {
							document.getElementById("tts-text").innerHTML += "Your Long Term Recommendation is " + recResponse.tracks[0].name + " by " + recResponse.tracks[0].artists[0].name + "\n " ;
							userLongRecPlaceholder.innerHTML = userLongRecTemplate(recResponse);
							console.log(recResponse);
					}
					});
				  }
				  
                }
            });
			
			
			$.ajax({
                url: 'https://api.spotify.com/v1/me/top/artists',
                headers: {
                  'Authorization': 'Bearer ' + access_token
                },
				data: {"limit": "10","time_range":"short_term"},
				limghdhit: 10,
				offset: 0,
				time_range:'short_term',
				json: true,
                success: function(response) {
				  shortResponse = response;
                  $('#login').hide();
                  $('#loggedin').show();
				  if (response.items.length > 0){
				    userShortFavPlaceholder.innerHTML = userShortFavTemplate(response);
					console.log(shortResponse);
					var artists = 5
					if (response.items.length < 5) {
						artists = response.items.length;
					}
					var i;
					
					var artistList = response.items[0].id;
					var artistNameList = response.items[0].name;
					
					for (i = 1; i < artists; i++){
						artistList += "," + response.items[i].id;
						artistNameList += ", " + response.items[i].name;
						
					}
					
					document.getElementById("tts-text").innerHTML += "Your Top Short Term artists are: " + artistNameList + "\n ";
					
					console.log(artistList);
					$.ajax({
						url: 'https://api.spotify.com/v1/recommendations',
						headers: {
						  'Authorization': 'Bearer ' + access_token
						},
						data: {"seed_artists": artistList,"min_popularity": "50", "limit" : "10"},
						json: true,
						success: function(recResponse) {
							document.getElementById("tts-text").innerHTML += "Your Short Term Recommendation is " + recResponse.tracks[0].name + " by " + recResponse.tracks[0].artists[0].name + "\n " ;
							userShortRecPlaceholder.innerHTML = userShortRecTemplate(recResponse);
							console.log(recResponse);
					}
					});
				  }
				  
                }
            });
          } else {
              $('#login').show();
			  document.getElementById("tts-text").innerHTML = "Please login in order to allow our app to make recommendations."
              $('#loggedin').hide();
          }
		  
		  
          document.getElementById('login-button').addEventListener('click', function() {

            var client_id = '50827088dd9a450cab32c88509bf85f3'; // Your client id
            var redirect_uri = 'http://project3/recommender/'; // Your redirect uri
			//var redirect_uri = 'http://people.tamu.edu/~jcarpman100/Project_3/recommender/'; // Your redirect uri

            var state = generateRandomString(16);

            localStorage.setItem(stateKey, state);
            var scope = 'user-read-private user-read-email user-top-read';

            var url = 'https://accounts.spotify.com/authorize';
            url += '?response_type=token';
            url += '&client_id=' + encodeURIComponent(client_id);
            url += '&scope=' + encodeURIComponent(scope);
            url += '&redirect_uri=' + encodeURIComponent(redirect_uri);
            url += '&state=' + encodeURIComponent(state);

            window.location = url;
          }, false);
        
      })();
    </script>
	<script src="../text2speech-test.js"></script>
<center>
	
	<?php
		
		/*if(!session_id()) {session_start();}
		else {
			$colorBlind = $_SESSION['colorBlind'];
			$poorSight = $_SESSION['poorSight'];
			setcookie("poorSight", $poorSight, time()+3600);
			setcookie("colorBlind", $colorBlind, time()+3600);
		}*/
		
		/*if (isset($_COOKIE["poorSight"])){
			$poorSight = $_COOKIE["poorSight"];
			$colorBlind = $_COOKIE["colorBlind"];
		} else */if (!isset($poorSight)){
			$poorSight = "no";
			$colorBlind = "normal";
		}
		
		
		 global $poorSight;
         global $colorBlind;
		
		/*if (isset($_POST["submit"])): 

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
		 */
		 
      ?>
	
<!--<form action = # method = "POST">
	<label for="poorSight">Would you like your results converted to text?: </label>
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
	<input type="submit" name="submit" value="Submit"/>
</form> -->
	<?php if($poorSight == "yes"){
			echo "<center><target=\"_blank\"> <button id = \"tts-button\" class = \"button\" style = \"width:100%\">Convert this page to audio</button></a></center>";
		}
		?> <br>
	Current TTS: <?php echo $poorSight; ?> <br>
	Current Color Sight: <?php echo $colorBlind; ?>
</center>
 
</html>
