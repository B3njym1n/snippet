package org.example;

import com.itextpdf.io.image.ImageData;
import com.itextpdf.io.image.ImageDataFactory;
import com.itextpdf.kernel.color.Color;
import com.itextpdf.kernel.pdf.PdfDocument;
import com.itextpdf.kernel.pdf.PdfWriter;
import com.itextpdf.kernel.pdf.canvas.draw.SolidLine;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.border.Border;
import com.itextpdf.layout.element.Cell;
import com.itextpdf.layout.element.Image;
import com.itextpdf.layout.element.LineSeparator;
import com.itextpdf.layout.element.Table;
import io.vavr.Tuple2;
import io.vavr.collection.Array;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import static com.itextpdf.kernel.geom.PageSize.A4;
import static io.vavr.API.*;

public class TablePdf {

    final Logger logger = LoggerFactory.getLogger(TablePdf.class);
    public static void main(String[] args) {
        try {
            new TablePdf().createPdf("tablePrintTest.pdf");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void createPdf(String dest) throws IOException {
        PdfDocument pdf = new PdfDocument(new PdfWriter(dest));
        pdf.setDefaultPageSize(A4);
        Document document = new Document(pdf);
        logger.info("pdf default size: " + pdf.getDefaultPageSize().toString());
        List<Tuple2<String, Object>> formData = constructData();

        SolidLine sl = new SolidLine(1f);
        sl.setColor(Color.MAGENTA);
        LineSeparator ls1 = new LineSeparator(sl);
//        ls1.setWidthPercent(0.5f);
//        ls1.setMarginBottom(80);
        document.add(ls1);
//        Paragraph p1 = new Paragraph().add("");
//        document.add(p1);
        int layout = 12;
        int[] cols = new int[] {2,4,2,4};
        Table table = new Table(layout);
        table.setMarginTop(40);
        table.setBorder(Border.NO_BORDER);
        table.addHeaderCell(new Cell(1,2).add("key").setBorder(Border.NO_BORDER));
        table.addHeaderCell(new Cell(1,4).add("value").setBorder(Border.NO_BORDER));
        table.addHeaderCell(new Cell(1,2).add("key").setBorder(Border.NO_BORDER));
        table.addHeaderCell(new Cell(1,4).add("value").setBorder(Border.NO_BORDER));
//        Table table = new Table(new float[]{28, 36, 28, 36});
        int columns = 2;
        int rows = formData.size() / columns;
        if (formData.size() % columns > 0) rows += 1;
//        Array.range(0, rows).crossProduct(Array.range(0, columns)).forEach(t -> System.out.println(t._1 + "/" + t._2));
        Array.range(0, rows).crossProduct(Array.range(0, columns)).forEach(t -> {
            /*if (t._1 * columns + t._2 == formData.size()) {
                table.addCell(new Cell(1, cols[0]));
                table.addCell(new Cell(1, cols[1]));
            } else {
                Tuple2<String, Object> data = formData.get(t._1 * columns + t._2);
                table.addCell(new Cell(1, cols[0]).add(data._1));
                table.addCell(new Cell(1, cols[1]).add((String) data._2));
            }*/
            Tuple2<Cell, Cell> z = Match(t._1 * columns + t._2).of(
                    Case($(formData.size()), () -> {
                        Tuple2<Cell, Cell> unit = new Tuple2<>(new Cell(1, cols[0]), new Cell(1, cols[1]));
                        return unit;
                    }),
                    Case($(), () -> {
                        Tuple2<String, Object> data = formData.get(t._1 * columns + t._2);
                        return data.map((k, v) -> new Tuple2<>(new Cell(1, cols[0]).add(k), new Cell(1, cols[1]).add((String) v)));
                        /*Tuple2<Cell, Cell> unit = new Tuple2<>(new Cell(1, cols[0]).add(data._1), new Cell(1, cols[1]).add((String) data._2));
                        return unit;*/
                    })
            );
            table.addCell(z._1);
            table.addCell(z._2);
        });

        ImageData img = ImageDataFactory.create("azovstal.jpg");
        document.add(table);
        Table table2 = new Table(2);
        table2.addCell(new Image(img).setAutoScale(true));
        table2.addCell("img");
        document.add(table2);
        document.add(new Image(img));
        document.close();
    }

    List<Tuple2<String, Object>> constructData() {
        List<Tuple2<String, Object>> data = new ArrayList<>();
        for (int i = 1; i < 34; i++) {
            data.add(new Tuple2<>("field" + i, "value" + i));
        }
        return data;
    }
}