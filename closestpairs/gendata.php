<?php
	for ($j = 0; $j < 90; $j++)
	{
		$numberPoints = rand(5000,10000);
		echo $numberPoints . "\n";
		for ($i = 0; $i < $numberPoints; $i++)
		{
			echo rand(0,1000000) / 100;
			echo " ";
			echo rand(0,1000000) / 100;
			echo "\n";
		}
	}   
	echo 0;
?>
