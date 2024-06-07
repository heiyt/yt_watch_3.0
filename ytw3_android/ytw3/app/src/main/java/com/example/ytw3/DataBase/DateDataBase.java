package com.example.ytw3.DataBase;

import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;
import java.util.List;

public class DateDataBase extends SQLiteOpenHelper{
    private static final String DATABASE_NAME = "data.db";
    private static final int DATABASE_VERSION = 1;
    public static final String TABLE_NAME = "remains";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_DATA = "data";
    public static final String COLUMN_DATA_THING = "data_things";
    public DateDataBase(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }
    @Override
    public void onCreate(SQLiteDatabase db) {
        String createTable = "CREATE TABLE " + TABLE_NAME + " (" +
                COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                COLUMN_DATA + " TEXT, " +
                COLUMN_DATA_THING + " TEXT)";
        db.execSQL(createTable);
    }
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }
    public void insertDataThings(String data,String thing) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(COLUMN_DATA, data);
        values.put(COLUMN_DATA_THING, thing);
        db.insert(TABLE_NAME, null, values);
        db.close();
    }
    public List<DateDataBase.DataRecord> getAllDataThings() {
        List<DataRecord> DataList = new ArrayList<>();
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_NAME, null, null, null, null, null, null);
        if (cursor.moveToFirst()) {
            do {
                @SuppressLint("Range") String data = cursor.getString(cursor.getColumnIndex(COLUMN_DATA));
                @SuppressLint("Range") String thing = cursor.getString(cursor.getColumnIndex(COLUMN_DATA_THING));
                DataList.add(new DataRecord(data,thing));
            } while (cursor.moveToNext());
        }
        cursor.close();
        db.close();
        return DataList;
    }
    public static class DataRecord {
        private final String data;
        private final String thing;
        public DataRecord(String data,String thing) {
            this.data = data;
            this.thing = thing;
        }
        public String getThing() {
            return thing;
        }
        public String getData() {
            return data;
        }
    }
    public void deleteDataThing(String data,String thing) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_NAME, COLUMN_DATA_THING + " = ? AND" + COLUMN_DATA + " = ?", new String[]{thing, data});
        db.delete(TABLE_NAME, COLUMN_ID + " = (SELECT MAX(" + COLUMN_ID + ") FROM " + TABLE_NAME + ")", null);
        db.close();
    }
}
