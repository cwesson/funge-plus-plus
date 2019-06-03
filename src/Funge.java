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
		String std = "be98";
		String filepath = "";
		for(String arg : args) {
			if(arg.startsWith("-std=")) {
				String parts[] = arg.split("=");
				std = parts[1];
			}else {
				filepath = arg;
			}
		}
		
		if(filepath == "") {
			System.err.println("No input file specified.");
			return;
		}
		
		try{
			File file = new File(filepath);
			PushbackInputStream fis = new PushbackInputStream(new FileInputStream(file));
			//Read code
			Field field = new Field(file);
			FungeRunner runner = new FungeRunner(field);
			new Thread(runner).start();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}

