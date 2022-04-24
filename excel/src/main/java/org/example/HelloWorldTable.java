package org.example;

import com.itextpdf.kernel.color.Color;
import com.itextpdf.kernel.pdf.PdfDocument;
import com.itextpdf.kernel.pdf.PdfWriter;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.element.Cell;
import com.itextpdf.layout.element.Table;
import com.itextpdf.layout.property.TextAlignment;
import com.itextpdf.layout.property.VerticalAlignment;

import java.io.FileNotFoundException;
import java.io.IOException;

public class HelloWorldTable {
    public void createPdf(String dest) throws IOException, FileNotFoundException {
        PdfDocument pdf = new PdfDocument(new PdfWriter(dest));
        Document document = new Document(pdf);
        Table table = new Table(3);
        Cell cell = new Cell(1, 3)
                .setTextAlignment(TextAlignment.CENTER)
                .add("Cell with colspan 3");
        table.addCell(cell);
        cell = new Cell(2, 1)
                .add("Cell with rowspan 2")
                .setVerticalAlignment(VerticalAlignment.MIDDLE);
        table.addCell(cell);
        table.addCell("Cell 1.1");
        table.addCell(new Cell().add("Cell 1.2"));
        table.addCell(new Cell()
                .add("Cell 2.1")
                .setBackgroundColor(Color.LIGHT_GRAY)
                .setMargin(5));
        table.addCell(new Cell()
                .add("Cell 1.2")
                .setBackgroundColor(Color.LIGHT_GRAY)
                .setPadding(5));
        document.add(table);
        document.close();
    }

    public static void main(String[] args) {
        try {
            new HelloWorldTable().createPdf("HelloWorldTable.pdf");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
