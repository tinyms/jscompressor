/*
 * for batch js or css compress.
 * author: tinyms.
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
                final StringBuffer sb1 = new StringBuffer();
                for (String fileFullPath : files) {
                    String baseName = FilenameUtils.getBaseName(fileFullPath);
                    String outputFileName = FilenameUtils.getFullPath(fileFullPath) + baseName + ".min." + FilenameUtils.getExtension(fileFullPath);
                    minFiles.add(outputFileName);
                    File output = new File(outputFileName);
                    if (output.exists()) {
                        output.delete();
                    }
                    compress(new File(fileFullPath), output, _type, _folder, sb1);
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
                        File output4aio = new File(_folder + "/allinone.min." + _type);
                        if (output4aio.exists()) {
                            output4aio.delete();
                        }
                        FileUtils.writeStringToFile(output4aio, sb.toString(), "UTF-8");
                    } catch (IOException ex) {
                        Logger.getLogger(Compressorhelper.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        }
    }

    public static String compress(final File f, File output, String _type, String _folder, final StringBuffer sb) {
        try {
            try {
                Reader in = new InputStreamReader(new FileInputStream(f), "UTF-8");
                if ("js".equals(_type)) {
                    try {
                        JavaScriptCompressor compressor = new JavaScriptCompressor(in, new ErrorReporter() {

                            @Override
                            public void warning(String message, String sourceName,
                                    int line, String lineSource, int lineOffset) {
                                if (line < 0) {
                                    //System.err.println("[WARNING] " + message+"\n");
                                    sb.append("[FILE] ").append(f.getAbsolutePath()).append("\n");
                                    sb.append("[WARNING] ").append(message).append("\n\n");
                                } else {
                                    //System.err.println("[WARNING] " + line + ':' + lineOffset + ':' + message+"\n");
                                    sb.append("[FILE] ").append(f.getAbsolutePath()).append("\n");
                                    sb.append("[WARNING] ").append(line).append(':').append(lineOffset).append(':').append(message).append("\n\n");
                                }
                            }

                            @Override
                            public void error(String message, String sourceName,
                                    int line, String lineSource, int lineOffset) {
                                if (line < 0) {
                                    //System.err.println("[ERROR] " + message+"\n");
                                    sb.append("[FILE] ").append(f.getAbsolutePath()).append("\n");
                                    sb.append("[ERROR] ").append(message).append("\n\n");
                                } else {
                                    //System.err.println("[ERROR] " + line + ':' + lineOffset + ':' + message+"\n");
                                    sb.append("[FILE] ").append(f.getAbsolutePath()).append("\n");
                                    sb.append("[ERROR] ").append(line).append(':').append(lineOffset).append(':').append(message).append("\n\n");
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
                } else if ("css".equals(_type)) {
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
        try {
            FileUtils.writeStringToFile(new File(_folder + "/console.log"), sb.toString(),"UTF-8");
        } catch (IOException ex) {
            Logger.getLogger(Compressorhelper.class.getName()).log(Level.SEVERE, null, ex);
        }
        return "";
    }
}
