package org.example;

import com.itextpdf.io.font.FontConstants;
import com.itextpdf.kernel.font.PdfFont;
import com.itextpdf.kernel.font.PdfFontFactory;
import com.itextpdf.kernel.geom.Rectangle;
import com.itextpdf.kernel.pdf.PdfDocument;
import com.itextpdf.kernel.pdf.PdfWriter;
import com.itextpdf.layout.ColumnDocumentRenderer;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.element.Paragraph;
import com.itextpdf.layout.property.TextAlignment;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;



public class Text2PdfColumns {
    static String TEXT = "file.txt";
    public void createPdf(String dest) throws IOException {
        PdfDocument pdf = new PdfDocument(new PdfWriter(dest));
        Document document = new Document(pdf)
                .setTextAlignment(TextAlignment.JUSTIFIED);
        Rectangle[] columns = {
                new Rectangle(36, 36, 254, 770),
                new Rectangle(305, 36, 254, 770)};
        document.setRenderer(new ColumnDocumentRenderer(document, columns));
        BufferedReader br = new BufferedReader(new FileReader(TEXT));
        String line;
        PdfFont normal = PdfFontFactory.createFont(FontConstants.TIMES_ROMAN);
        PdfFont bold = PdfFontFactory.createFont(FontConstants.TIMES_BOLD);
        boolean title = true;
        while ((line = br.readLine()) != null) {
            document.add(new Paragraph(line).setFont(title ? bold : normal));
            title = line.isEmpty();
        }
        document.close();
    }

    public static void main(String[] args) {
        try {
            new Text2PdfColumns().createPdf("Text2PdfColumns7.pdf");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
