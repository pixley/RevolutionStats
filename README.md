# RevolutionStats

Stream visualizer for Twitch Plays Pokémon Battle Revolution stats.

This was created to serve as a visual aid for people watching Pixley Commentates Twitch, so as to make the combatants' stats more visible to the viewer, and as an aid to me so I could give more informed commentary.

For now, RevolutionStats is Windows-only.  I may further explore cross-platform releases if there is demand, though, I'd imagine few people stream from Mac or Linux.

##Features

###Stat display

This is the primary display for RevolutionStats, as it is the window where the stats themselves are displayed.  The Red and Blue Teams stats are displayed in opposition.  The stat display also features a customizable background, which can be changed by replacing Bkg.png in the RevolutionStats folder.  It should be noted that the displayed text is made under the assumption of a dark background, so please pay attention to that.

###Console input

User control of RevolutionStats is not through the stat display window, but the console, which is intended to stay hidden from  stream viewers.  Upon starting RevolutionStats, the user is asked to input the combatants one at a time.  Then the console sits idly until the user decided to start a new match or exit the program.

##Final Thoughts

You can find Pixley Commentates Twitch, the show for which RevolutionStats was developed, on [my Twitch channel](http://twitch.tv/pixley).

RevolutionStats was built using SFML, a multimedia library which can be found at http://sfml-dev.org. SFML is the copyright of Laurent Gomila.
