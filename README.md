# procut
***under developement***

| It's a hobby project :) 

# cut video commande
	$ ffmpeg -i input -ss hh:mm:ss -to hh:mm:ss -async 1 output

# concatenate multiple videos
	step1: create a file containing all videos(you want to join) path
       		Example: $ touch list
			$ cat > list
		  	file 1st_video_path
		  	file 2st_video_path
		  	...
		  	^C
	step2: $ ffmpeg -safe 0 -f concat -i list -c copy output 




