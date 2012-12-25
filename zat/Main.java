import java.util.*;

public class Main {

	public static void main(String[] args) {
    	Scanner sc = new Scanner(System.in);
        while(true) {
    		int N = sc.nextInt();
    		int[] me0 = new int[4];
    		for(int i=0;i<4;i++){me0[i]=sc.nextInt();}
    		int[] me1 = new int[4];
    		for(int i=0;i<4;i++){me1[i]=sc.nextInt();}
    		int[] enemy0 = new int[4];
    		for(int i=0;i<4;i++){enemy0[i]=sc.nextInt();}
	    	int[] enemy1 = new int[4];
    		for(int i=0;i<4;i++){enemy1[i]=sc.nextInt();}
	    	System.out.println(judge(me0,me1,enemy0,enemy1));
    		System.out.flush();
        }
	    sc.close();
	}

	public static String judge(int[] me0,int[] me1,int[] enemy0,int[] enemy1){
		//3本ルール
		/*if(enemy0.equals(new int[]{1,1,1,0})){return ""+0+" "+0+" "+(3-whereisTerminal(me0)[0]);}
		if(enemy1.equals(new int[]{1,1,1,0})){return ""+0+" "+1+" "+(3-whereisTerminal(me0)[0]);}
		if(enemy0.equals(new int[]{0,1,1,1})){return ""+0+" "+0+" "+(0-whereisTerminal(me0)[1]);}
		if(enemy1.equals(new int[]{0,1,1,1})){return ""+0+" "+1+" "+(0-whereisTerminal(me0)[1]);}*/
		
		//基本はランダム
		return ""+(int)(Math.random() * 2)+" "+(int)(Math.random() * 2)+" "+((int)(Math.random() * 7) - 3);
	}
	
	public static int[] whereisTerminal(int[] hand){
		int[] answer={-1,-1};
		for(int i=0;i<4;i++){
			if(hand[i]==1){
				if(answer[0]==-1){answer[0]=i+1;}
				else{answer[1]=i+1;}
			}
		}
		return answer;
	}
	
}
