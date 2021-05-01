import java.io.BufferedReader;
import java.util.Scanner;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

public class TryHashTable extends HashTableImp{

	//initialize the table size
	public TryHashTable(int tableSize){
		super(tableSize);
	}

	public static void main(String[] args){
		String line = "";
		int tableSize = 0;

		if(args.length == 2){

			tableSize = Integer.valueOf(args[0]);
			TryHashTable hashMap = new TryHashTable(tableSize);

			//read the sample file
			String fileName = args[1];

			try(
				BufferedReader buferedReader = new BufferedReader(new FileReader(fileName))
			)
			{
				while((line = buferedReader.readLine()) != null){
					//convert all non alphbeticals to whitesapces
					String text = line.replaceAll("\\W"," ");

					//split the line from whitespaces
					String words[] = text.split("\\s+");

					for(String s : words){
						//insert into the hash table
						hashMap.insert(s);
					}
				}
			}catch(FileNotFoundException e){
				System.out.println("File does not exist");
				return;
			}
			catch (IOException e){
				System.out.println("File reading failed");
				return;
			}

			//print the report data
			hashMap.findBucketSize(tableSize);
			System.out.println();

			Scanner scannerKey = new Scanner(System.in);
			String key;

			System.out.println("Enter the key:");
			key = scannerKey.nextLine();
			System.out.println("Value: " + hashMap.search(key));

			while(!key.equals("Q")){
				System.out.println("Enter the key:");
				key = scannerKey.nextLine();
				System.out.println("Value: " + hashMap.search(key));
			}

		}else{
			System.out.println("Usage: java TryHashTable <number Of buckets> <filename.text>");
		}
	}
}


