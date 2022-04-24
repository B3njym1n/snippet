package org.example;

import com.itextpdf.io.font.FontConstants;
import com.itextpdf.kernel.color.Color;
import com.itextpdf.kernel.font.PdfFont;
import com.itextpdf.kernel.font.PdfFontFactory;
import com.itextpdf.kernel.pdf.PdfDocument;
import com.itextpdf.kernel.pdf.PdfWriter;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.Style;
import com.itextpdf.layout.element.Paragraph;
import com.itextpdf.layout.element.Text;

import java.io.IOException;

public class HelloWorldStyles {
    public void createPdf(String dest) throws IOException {
        PdfDocument pdf = new PdfDocument(new PdfWriter(dest));
        PdfFont code = PdfFontFactory.createFont(FontConstants.COURIER);
        Style style = new Style()
                .setFont(code)
                .setFontSize(12)
                .setFontColor(Color.RED)
                .setBackgroundColor(Color.LIGHT_GRAY);
            Document document = new Document(pdf);
            document.add(
                    new Paragraph()
                            .add("In this example, named ")
                            .add(new Text("HelloWorldStyles").addStyle(style))
                            .add(", we experiment with some text in ")
                            .add(new Text("code style").addStyle(style))
                            .add("."));
        document.close();
    }

    public static void main(String[] args) {
        try {
            new HelloWorldStyles().createPdf("HelloWorldStyles.pdf");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
