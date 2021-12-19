# Six Degrees of Kevin Bacon

The function of this program is to find paths from one actor to another, based on actors they have coacted before. The output will be in the form of a list of actors, with movie names acting as bridges between actors. The two actors on both sides of the bridge both appear in the bridging movie.

## Source file:
Format: &lt;moviename&gt; &lt;actor1&gt; &lt;actor2&gt; .... &lt;actorn&gt;

## Input file:
Format: &lt;actor1&gt; &lt;actor2&gt;

Program will find path between actor1 and actor2

## Output File
&lt;actor1&gt; -(&lt;movie name&gt;)- &lt;actor2&gt; -(&lt;movie name&gt;)- &lt;actor3&gt; .....