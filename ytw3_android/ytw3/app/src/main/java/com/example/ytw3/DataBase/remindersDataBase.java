package com.example.ytw3.DataBase;

import android.annotation.SuppressLint;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;
import java.util.List;

public class remindersDataBase extends SQLiteOpenHelper {
    private static final String DATABASE_NAME = "reminders.db";
    private static final int DATABASE_VERSION = 1;
    public static final String TABLE_NAME = "reminders";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_reminderS = "remindered_things";
    public remindersDataBase(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }
    @Override
    public void onCreate(SQLiteDatabase db) {
        String createTable = "CREATE TABLE " + TABLE_NAME + " (" +
                COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                COLUMN_reminderS + " TEXT)";
        db.execSQL(createTable);
    }
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }
    public void insertReminderThings(String things) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(COLUMN_reminderS, things);
        db.insert(TABLE_NAME, null, values);
        db.close();
    }
    public List<remindersDataBase.remindersRecord> getAllreminders() {
        List<remindersDataBase.remindersRecord> remindersList = new ArrayList<>();
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_NAME, null, null, null, null, null, null);
        if (cursor.moveToFirst()) {
            do {
                @SuppressLint("Range") String thing = cursor.getString(cursor.getColumnIndex(COLUMN_reminderS));
                remindersList.add(new remindersDataBase.remindersRecord(thing));
            } while (cursor.moveToNext());
        }
        cursor.close();
        db.close();
        return remindersList;
    }
    public void deleteThings(String thing) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_NAME, TABLE_NAME + " = ?", new String[]{thing});
        db.close();
    }
    public static class remindersRecord {
        private final String things;
        public remindersRecord(String things) {
            this.things = things;
        }
        public String getThings() {
            return things;
        }
    }
}
