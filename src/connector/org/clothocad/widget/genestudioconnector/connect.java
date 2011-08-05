/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.clothocad.widget.genestudioconnector;
import org.clothocore.api.plugin.ClothoWidget;
import java.io.*;
import javax.swing.*;
import org.ini4j.*; 
/**
 *
 * @author USTC_Software
 */
public class connect implements ClothoWidget{
    File f;

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
        f=new File(this.GetPath());
        Ini i=new Ini(f);        
        return i.get("designer", "apppath");
    }
    

    public String GetPath()
    {
        return System.getProperty("user.home")+"/.lachesis/lachesis.conf";        
    }

}
