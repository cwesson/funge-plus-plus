/**
 * @file Funge.java
 * Main class for a full functional Befunge-98 interperter.
 * @author Conlan Wesson
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.PushbackInputStream;

public class Funge{
	public static void main(String args[]){
		try{
			File file = new File(args[0]);
			PushbackInputStream fis = new PushbackInputStream(new FileInputStream(file));
			//Determine playfield size
			int width = 0;
			int height = 0;
			int count = 0;
			int i = 0;
			do{
				i = fis.read();
				if(i == '\n' || i == '\r' || i == -1){
					if(i == '\r'){
						int j = fis.read();
						if(j != '\n'){
							fis.unread(j);
						}
					}
					height++;
					if(count > width) width = count;
					count = 0;
				}else{
					count++;
				}
			}while(i > -1);
			fis.close();
			//Read code
			Field field = new Field(file, width, height);
			FungeRunner runner = new FungeRunner(field);
			new Thread(runner).start();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}

