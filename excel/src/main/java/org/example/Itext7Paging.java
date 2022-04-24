package org.example;

import com.itextpdf.io.font.FontConstants;
import com.itextpdf.kernel.color.Color;
import com.itextpdf.kernel.events.PdfDocumentEvent;
import com.itextpdf.kernel.font.PdfFont;
import com.itextpdf.kernel.font.PdfFontFactory;
import com.itextpdf.kernel.pdf.PdfDocument;
import com.itextpdf.kernel.pdf.PdfWriter;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.border.Border;
import com.itextpdf.layout.border.SolidBorder;
import com.itextpdf.layout.element.Paragraph;
import com.itextpdf.layout.property.TextAlignment;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Itext7Paging {
    static String TEXT = "file.txt";

    public static void main(String[] args) {
        Itext7Paging run = new Itext7Paging();
        try {
            run.createPdf("Paging.pdf");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void createPdf(String dest) throws IOException {
        PdfDocument pdf = new PdfDocument(new PdfWriter(dest));
        pdf.addEventHandler(PdfDocumentEvent.END_PAGE, new Footer());
        Document document = new Document(pdf)
                .setTextAlignment(TextAlignment.JUSTIFIED);
        BufferedReader br = new BufferedReader(new FileReader(TEXT));
        String line;
        PdfFont normal = PdfFontFactory.createFont(FontConstants.TIMES_ROMAN);
        PdfFont bold = PdfFontFactory.createFont(FontConstants.TIMES_BOLD);
        boolean title = true;
        Border border = new SolidBorder(Color.BLUE, 1);
        while ((line = br.readLine()) != null) {
            document.add(new Paragraph(line)
                    .setFont(title ? bold : normal)
                    .setBorder(title ? border : Border.NO_BORDER));
            title = line.isEmpty();
        }
        document.close();
    }
}
