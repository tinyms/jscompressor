/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.tinyms;

import com.yahoo.platform.yui.compressor.CssCompressor;
import com.yahoo.platform.yui.compressor.JavaScriptCompressor;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.FilenameUtils;
import org.apache.commons.lang.ArrayUtils;
import org.apache.commons.lang.StringUtils;
import org.mozilla.javascript.ErrorReporter;
import org.mozilla.javascript.EvaluatorException;

/**
 *
 * @author tinyms
 */
public class Compressorhelper {

    private static final Logger log = Logger.getAnonymousLogger();

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Map<String, String> argMap = new HashMap<String, String>();
        for (int k = 0; k < args.length; k = k + 2) {
            argMap.put(args[k], args[k + 1]);
            System.out.print(" " + args[k] + " " + args[k + 1] + "\r\n");
        }
        String _folder = argMap.get("-selected-folder");
        String _files = argMap.get("-files");
        String _allInOne = argMap.get("-aio");
        String _type = argMap.get("-type");
        if (StringUtils.isNotBlank(_files)) {
            List<String> minFiles = new ArrayList<String>();
            String[] files = StringUtils.split(_files, ";");
            if (ArrayUtils.isNotEmpty(files)) {
                for (String fileFullPath : files) {
                    String baseName = FilenameUtils.getBaseName(fileFullPath);
                    String outputFileName = FilenameUtils.getFullPath(fileFullPath) + baseName + ".min." + FilenameUtils.getExtension(fileFullPath);
                    minFiles.add(outputFileName);
                    compress(new File(fileFullPath), new File(outputFileName), _type);
                }
                if (StringUtils.isNotBlank(_allInOne)) {
                    StringBuilder sb = new StringBuilder();
                    for (String minFilePath : minFiles) {
                        File minFile = new File(minFilePath);
                        if (minFile.exists()) {
                            try {
                                sb.append(FileUtils.readFileToString(minFile, "UTF-8"));
                            } catch (IOException ex) {
                                Logger.getLogger(Compressorhelper.class.getName()).log(Level.SEVERE, null, ex);
                            }
                        }
                    }
                    try {
                        FileUtils.writeStringToFile(new File(_folder + "/allinone." + _type), sb.toString(), "UTF-8");
                    } catch (IOException ex) {
                        Logger.getLogger(Compressorhelper.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        }
    }

    public static String compress(File f, File output, String _type) {
        try {
            try {
                Reader in = new InputStreamReader(new FileInputStream(f), "UTF-8");
                if (_type.endsWith(".js")) {
                    try {
                        JavaScriptCompressor compressor = new JavaScriptCompressor(in, new ErrorReporter() {

                            @Override
                            public void warning(String message, String sourceName,
                                    int line, String lineSource, int lineOffset) {
                                if (line < 0) {
                                    System.err.println("\n[WARNING] " + message);
                                } else {
                                    System.err.println("\n[WARNING] " + line + ':' + lineOffset + ':' + message);
                                }
                            }

                            @Override
                            public void error(String message, String sourceName,
                                    int line, String lineSource, int lineOffset) {
                                if (line < 0) {
                                    System.err.println("\n[ERROR] " + message);
                                } else {
                                    System.err.println("\n[ERROR] " + line + ':' + lineOffset + ':' + message);
                                }
                            }

                            @Override
                            public EvaluatorException runtimeError(String message, String sourceName,
                                    int line, String lineSource, int lineOffset) {
                                error(message, sourceName, line, lineSource, lineOffset);
                                return new EvaluatorException(message);
                            }
                        });
                        in.close();
                        in = null;
                        Writer out = new OutputStreamWriter(new FileOutputStream(output), "UTF-8");
                        compressor.compress(out, -1, true, true, true, true);
                        out.close();
                    } catch (IOException ex) {
                        log.info(ex.getLocalizedMessage());
                    } catch (org.mozilla.javascript.EvaluatorException ex) {
                        log.info(ex.getLocalizedMessage());
                    }
                } else if (_type.endsWith(".css")) {
                    try {
                        CssCompressor compressor = new CssCompressor(in);
                        in.close();
                        in = null;
                        Writer out = new OutputStreamWriter(new FileOutputStream(output), "UTF-8");
                        compressor.compress(out, -1);
                        out.close();
                    } catch (IOException ex) {
                        log.info(ex.getLocalizedMessage());
                    }
                }
            } catch (FileNotFoundException ex) {
                log.info(ex.getLocalizedMessage());
            }
        } catch (UnsupportedEncodingException ex) {
            log.info(ex.getLocalizedMessage());
        }
        return "";
    }
}
