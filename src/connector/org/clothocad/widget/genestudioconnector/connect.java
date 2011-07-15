/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.clothocad.widget.genestudioconnector;
import org.clothocore.api.plugin.ClothoWidget;
import java.io.*;
import javax.swing.*;
/**
 *
 * @author USTC_Software
 */
public class connect implements ClothoWidget{
    File f;
    FileReader fr;
    BufferedReader br;

    @Override
    public void launch() {
        try{
        String tmp=this.prepare()+" -from-clotho";
        Runtime.getRuntime().exec(tmp);
        }
        catch(Exception e){
            JOptionPane.showConfirmDialog(null, "Cannot start GeneStudio please reconfigure it!","Launch Failed!",JOptionPane.CLOSED_OPTION,JOptionPane.WARNING_MESSAGE);
        }
       // throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void close() {
        try{
        String tmp=this.prepare()+" -close";
        Runtime.getRuntime().exec(tmp);
        }
        catch(Exception e){
            JOptionPane.showConfirmDialog(null, "Cannot close GeneStudio please reconfigure it!","Terminate Failed!",JOptionPane.CLOSED_OPTION,JOptionPane.WARNING_MESSAGE);
        }
        //throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void init() {
       // throw new UnsupportedOperationException("Not supported yet.");
    }
    public String prepare() throws Exception{
        String tmp=null;
        f=new File(this.GetPath());
        fr=new FileReader(f);
        br=new BufferedReader(fr);
        br.readLine();
        tmp=br.readLine();
        tmp=tmp.substring(8,tmp.length());
        this.br.close();
        this.fr.close();
        return tmp;
    }
    

    public String GetPath()
    {
        return System.getProperty("user.home")+"/.genestudio/genestudio.conf";        
    }

}
