<!-- Homepage -->

<!DOCTYPE html>
<html lang="en-US"> 

<head>
<meta charset="UTF-8">

<?php
	if (isset($_COOKIE["poorSight"])){
			$poorSight = $_COOKIE["poorSight"];
			$colorBlind = $_COOKIE["colorBlind"];
		} else if (!isset($poorSight)){
			$poorSight = "no";
			$colorBlind = "normal";
		}
	?>

<link rel="stylesheet" href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css">
<link rel="stylesheet" type="text/css" href="../content/style.php" media="screen"></link>

<center>
<a href="index.html" rel="home">
		</a></center>

<!--<body bgcolor = "#1DB954">style="font-size:0px"-->
<center>
<div class = buttonHolder>
<a href="../index.php"> <button class = "button">[Home]</button></a>
<a href="../recommender/index.php"> <button class = "button">[Music Recommender]</button></a>
<a href="../visual/index.php"> <button class = "button">[Taste Visualizer]</button></a>
<a href="../bands/index.php"> <button class = "button currentButton">[Nearby Bands]</button></a>
<!--<a href="accom/index.html"> <button class = "button">[Accommodation]</button></a-->
</div></center>
</body>


</div></div>
<script charset="utf-8" src="https://widget.bandsintown.com/main.min.js"></script>

	<body>
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
        <h3>Please login in order to allow our app to find live music from your favorite artists.</h3>
        <button id="login-button" class="btn btn-primary">Log in with Spotify</button>
		</center>
      </div>
      <div id="loggedin">
        <div id="user-profile">
        </div>
		<div id="user-long-fav">
		</div>
		<div id="user-long-band">
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
      <div class="media">
        <!--<div class="pull-left">
          <img class="media-object" width="150" src="{{images.0.url}}" />
        </div>-->
      </div>
	  </body>
    </script>
	
	<script id="user-long-band-template" type="text/x-handlebars-template">
	<body>
	<br>
  
        <!--<div class="pull-left">
          <img class="media-object" width="150" src="{{images.0.url}}" />
        </div>-->
		<div class="media-body" width = "50%">
		
		{{#each items}}
		 <h2>{{this.name}}</h2>
		 <a class="bit-widget-initializer" data-artist-name="{{this.name}}" data-display-local-dates="true" data-display-past-dates="false" data-auto-style="true" data-text-color="#000000" data-link-color="#00b4b3" data-background-color="rgba(0,0,0,0)" data-display-limit="" data-display-start-time="false" data-link-text-color="#FFFFFF" data-display-lineup="false" data-display-play-my-city="false" data-separator-color="rgba(255, 255, 255, 0.5)"></a>				
		
		 <br>
		 {{/each}}
		 </div>
		 
		 <hr align = "left" style = "background-color:black;height:2px">
		 </div>
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
			
			userLongBandSource = document.getElementById('user-long-band-template').innerHTML,
            userLongBandTemplate = Handlebars.compile(userLongBandSource),
            userLongBandPlaceholder = document.getElementById('user-long-band');

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
          if (access_token) {
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
			
			$.ajax({
                url: 'https://api.spotify.com/v1/me/top/artists',
                headers: {
                  'Authorization': 'Bearer ' + access_token
                },
				data: {"limit": 3,"time_range":"long_term"},
				offset: 0,
				time_range:'long_term',
				json: true,
                success: function(response) {
				  longResponse = response;
                  $('#login').hide();
                  $('#loggedin').show();
				  if (response.items.length > 0){
				    userLongFavPlaceholder.innerHTML = userLongFavTemplate(response);
					userLongBandPlaceholder.innerHTML = userLongBandTemplate(response);
					console.log(longResponse);
					/*var artists = 10
					if (response.items.length < 10) {
						artists = response.items.length;
					}
					var i;
					var artistList = response.items[0].id;
					for (i = 1; i < artists; i++){
						artistList += "," + response.items[i].id;
					}
					console.log(artistList);
					$.ajax({
						url: 'https://api.spotify.com/v1/recommendations',
						headers: {
						  'Authorization': 'Bearer ' + access_token
						},
						data: {"seed_artists": artistList,"min_popularity": "50", "limit" : "10"},
						json: true,
						success: function(recResponse) {
							userLongRecPlaceholder.innerHTML = userLongRecTemplate(recResponse);
							console.log(recResponse);
					}
					});*/
				  }
				  
                }
            });
          } else {
              $('#login').show();
              $('#loggedin').hide();
          }

          document.getElementById('login-button').addEventListener('click', function() {

            var client_id = '50827088dd9a450cab32c88509bf85f3'; // Your client id
            //var redirect_uri = 'http://project3/bands/'; // Your redirect uri
			var redirect_uri = 'http://people.tamu.edu/~jcarpman100/Project_3/bands/'; // Your redirect uri

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
<center>
			
			
			
			<a class="bit-widget-initializer" data-artist-name="" data-display-local-dates="true" data-display-past-dates="false" data-auto-style="true" data-text-color="#000000" data-link-color="#00b4b3" data-background-color="rgba(0,0,0,0)" data-display-limit="" data-display-start-time="false" data-link-text-color="#FFFFFF" data-display-lineup="false" data-display-play-my-city="false" data-separator-color="rgba(255, 255, 255, 0.5)"></a>				
			
				</body>
				
				<br style="clear:left;"/>
				<hr>
<center>
	
	<?php
		
		/*if(!session_id()) {session_start();}
		else if (isset($_SESSION['colorBlind']) && isset($_SESSION['poorSight'])) { 
			$colorBlind = $_SESSION['colorBlind'];
			$poorSight = $_SESSION['poorSight'];
			setcookie("poorSight", $poorSight, time()+3600);
			setcookie("colorBlind", $colorBlind, time()+3600);
		}*/
		
		if (isset($_COOKIE["poorSight"])){
			$poorSight = $_COOKIE["poorSight"];
			$colorBlind = $_COOKIE["colorBlind"];
		} else if (!isset($poorSight)){
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
	 echo "<center><target=\"_blank\"> <button class = \"button\" style = \"width:100%\">Convert this page to audio</button></a></center>";
	}
	?> <br>
	Current TTS: <?php echo $poorSight; ?> <br>
	Current Color Sight: <?php echo $colorBlind; ?>
	
</center>
 
</html>
