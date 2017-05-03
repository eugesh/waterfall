// #include <chrono>
// #include <thread>
#include <iostream>
#include <unistd.h>
#include <QVector>
#include <gdal_priv.h>
#include "sonar_emu_thread.h"
#include <cpp-hyscan-db-wrap.h>
#include <cpp-hyscan-acoustic-data.h>

SonarEmuSts::SonarEmuSts () {
    _time_delay = 1.0;
}

SonarEmuThread::SonarEmuThread (QObject *parent) : QThread (parent) {
   progressbar = NULL;
}

void SonarEmuThread::start_sonar_emu_view () {
    int first_ln = get_first_index_in_range (_acoustic_channel_id);
    int last_ln = get_last_index_in_range (_acoustic_channel_id);

    // connect (this,SIGNAL (number_worked_lines (int)), progressbar, SLOT (setValue (int)));

    std::cout << "first_ln = " << first_ln << '\n';
    std::cout << "last_ln = " << last_ln << '\n';
    std::cout << "_fullname_tmp_tiff = " << qPrintable (_fullname_tmp_tiff) << '\n';

    GDALDataset *pdata;

    if (!_fullname_tmp_tiff.isEmpty ()) {
        // FULL CYCLE
        for (int i = first_ln; i < last_ln; ++i) {
            // Открытие файла на запись
            pdata = (GDALDataset*)GDALOpen(_fullname_tmp_tiff.toLocal8Bit().data(), GA_Update);
            if (pdata != 0) {
                // Buffer for acoustic data
                unsigned int buf_size = get_values_count(_acoustic_channel_id, i);
                std::cout << "buf_size = " << buf_size << '\n';
                float *raw_float_buf = new float[buf_size];
                unsigned char *raw_uchar_buf = new unsigned char[buf_size];
                unsigned char *raw_uchar_buf_ovr4 = new unsigned char[static_cast<int>(buf_size/4)];
                unsigned char *raw_uchar_buf_ovr8 = new unsigned char[static_cast<int>(buf_size/8)];
                unsigned char *raw_uchar_buf_ovr16 = new unsigned char[static_cast<int>(buf_size/16)];
                if (buf_size > 0) {
                    // Read acoustic data from DB
                    // unsigned int buf_size_check = get_values (_acoustic_channel_id, i, buf.data(), buf_size);
                    unsigned int buf_size_check = get_values (_acoustic_channel_id, i, raw_float_buf, buf_size);
                    // for (int j = 0; j < buf_size_check; ++j)
                        // buf_uchar[j] = static_cast<unsigned char>(buf[j] * 255.0);
                    for (int j = 0; j < buf_size_check; ++j) {
                        raw_uchar_buf[j] = static_cast<unsigned char>(raw_float_buf[j] * 255.0 * 4);
                        if (j < static_cast<int>(buf_size/4))
                            raw_uchar_buf_ovr4[j] = static_cast<unsigned char>(raw_float_buf[j * 4] * 255.0 * 2);
                        if (j < static_cast<int>(buf_size/8))
                            raw_uchar_buf_ovr8[j] = static_cast<unsigned char>(raw_float_buf[j * 8] * 255.0 * 2);
                        if (j < static_cast<int>(buf_size/16))
                            raw_uchar_buf_ovr16[j] = static_cast<unsigned char>(raw_float_buf[j * 16] * 255.0 * 2);
                    }

                    // Write acoustic data to tmp.tif
                    pdata->RasterIO (GF_Write, 0, i, buf_size_check, 1, raw_uchar_buf, buf_size_check, 1, GDT_Byte, 1, NULL, 0, 0, 0);
                    // pdata->RasterIO (GF_Write, 0, i, buf_size_check, 1, raw_buf, buf_size_check, 1, GDT_Float32, 1, NULL, 0, 0, 0);
                    // pdata->RasterIO (GF_Write, i, 0, 1, buf_size_check, buf.data(), 1, buf_size_check, GDT_Float32, 1, NULL, 0, 0, 0);
                    // pdata->RasterIO (GF_Write, i, 0, 1, buf_size_check, buf.data(), 1, buf_size_check, GDT_Byte, 1, NULL, sizeof(unsigned char));
                    // Write data to overviews with corresponding scale
                    ///-----Обновление имеющихсЯ копий-------------------------------------
                    int anOverviewList[3] = { 4, 8, 16};
                    pdata->BuildOverviews ("NEAREST", 3, anOverviewList, 0, NULL, NULL, NULL);

                    delete[]raw_float_buf;
                    delete[]raw_uchar_buf;
                    delete[]raw_uchar_buf_ovr4;
                    delete[]raw_uchar_buf_ovr8;
                    delete[]raw_uchar_buf_ovr16;
                    emit number_worked_lines(i);
                }
            }
            GDALClose(pdata);

            // Pause
            usleep(_time_delay * 1000000);
            std::cout << "Read line, _time_delay = " << _time_delay << '\n';
            // std::this_thread::sleep_for(std::chrono::milliseconds(_time_delay));
        }
    }
}

void SonarEmuThread::start_write_tiff () {
    int first_ln = get_first_index_in_range (_acoustic_channel_id);
    int last_ln = get_last_index_in_range (_acoustic_channel_id);

    // connect (this,SIGNAL (number_worked_lines (int)), progressbar, SLOT (setValue (int)));

    std::cout << "first_ln = " << first_ln << '\n';
    std::cout << "last_ln = " << last_ln << '\n';
    std::cout << "_fullname_tmp_tiff = " << qPrintable (_fullname_tmp_tiff) << '\n';

    GDALDataset *pdata;

    if (!_fullname_tmp_tiff.isEmpty ()) {
        // Открытие файла на запись
        pdata = (GDALDataset*)GDALOpen(_fullname_tmp_tiff.toLocal8Bit().data(), GA_Update);
        if (pdata != 0) {
        // FULL CYCLE
            for (int i = first_ln; i < last_ln; ++i) {
                // Buffer for acoustic data
                unsigned int buf_size = get_values_count(_acoustic_channel_id, i);
                std::cout << "buf_size = " << buf_size << '\n';
                float *raw_float_buf = new float[buf_size];
                unsigned char *raw_uchar_buf = new unsigned char[buf_size];
                if (buf_size > 0) {
                    // Read acoustic data from DB
                    unsigned int buf_size_check = get_values (_acoustic_channel_id, i, raw_float_buf, buf_size);
                    for (int j = 0; j < buf_size_check; ++j) {
                        raw_uchar_buf[j] = static_cast<unsigned char>(raw_float_buf[j] * 255.0 * 4);
                    }

                    // Write acoustic data to tmp.tif
                    pdata->RasterIO (GF_Write, 0, i, buf_size_check, 1, raw_uchar_buf, buf_size_check, 1, GDT_Byte, 1, NULL, 0, 0, 0);

                    delete[]raw_float_buf;
                    delete[]raw_uchar_buf;
                    emit number_worked_lines(i);
                }
            }
            ///-----Построение или обновление имеющихсЯ копий-------------------------------------
            int anOverviewList[3] = { 4, 8, 16};
            pdata->BuildOverviews ("NEAREST", 3, anOverviewList, 0, NULL, NULL, NULL);
            GDALClose(pdata);
        }
    }
}

void SonarEmuThread::start_write_full_tiff () {
    int first_ln = get_first_index_in_range (_acoustic_channel_id);
    int last_ln = get_last_index_in_range (_acoustic_channel_id);

    // connect (this,SIGNAL (number_worked_lines (int)), progressbar, SLOT (setValue (int)));

    std::cout << "first_ln = " << first_ln << '\n';
    std::cout << "last_ln = " << last_ln << '\n';
    std::cout << "_fullname_tmp_tiff = " << qPrintable (_fullname_tmp_tiff) << '\n';

    GDALDataset *pdata;

    const char ** track_list = get_track_list (_project_id);
    std::cout << "_project_id = " << _project_id << '\n';
    for (int i = 0; track_list[i] != 0; ++i)
        std::cout << "track_list[" << i << "] = " << track_list[i] << '\n';

    if (!_fullname_tmp_tiff.isEmpty ()) {
        // Открытие файла на запись
        pdata = (GDALDataset*)GDALOpen(_fullname_tmp_tiff.toLocal8Bit().data(), GA_Update);
        if (pdata != 0) {
        // FULL CYCLE
            for (int i = first_ln; i < last_ln; ++i) {
                // Buffer for acoustic data
                unsigned int buf_size = get_values_count(_acoustic_channel_id, i);
                std::cout << "buf_size = " << buf_size << '\n';
                float *raw_float_buf = new float[buf_size];
                unsigned char *raw_uchar_buf = new unsigned char[buf_size];
                if (buf_size > 0) {
                    // Read acoustic data from DB
                    unsigned int buf_size_check = get_values (_acoustic_channel_id, i, raw_float_buf, buf_size);
                    for (int j = 0; j < buf_size_check; ++j) {
                        raw_uchar_buf[j] = static_cast<unsigned char>(raw_float_buf[j] * 255.0 * 4);
                    }

                    // Write acoustic data to tmp.tif
                    pdata->RasterIO (GF_Write, 0, i, buf_size_check, 1, raw_uchar_buf, buf_size_check, 1, GDT_Byte, 1, NULL, 0, 0, 0);

                    delete[]raw_float_buf;
                    delete[]raw_uchar_buf;
                    emit number_worked_lines(i);
                }
            }
            ///-----Обновление имеющихсЯ копий-------------------------------------
            int anOverviewList[3] = { 4, 8, 16};
            pdata->BuildOverviews ("NEAREST", 3, anOverviewList, 0, NULL, NULL, NULL);
            GDALClose(pdata);
        }
    }
}

/*
void SonarEmuThread::run () {
    int first_ln = get_first_index_in_range (_acoustic_channel_id);
    int last_ln = get_last_index_in_range (_acoustic_channel_id);

    // connect (this,SIGNAL (number_worked_lines (int)), progressbar, SLOT (setValue (int)));

    std::cout << "first_ln = " << first_ln << '\n';
    std::cout << "last_ln = " << last_ln << '\n';
    std::cout << "_fullname_tmp_tiff = " << qPrintable (_fullname_tmp_tiff) << '\n';

    GDALDataset *pdata;

    if (!_fullname_tmp_tiff.isEmpty ()) {
        // FULL CYCLE
        for (int i = first_ln; i < last_ln; ++i) {
            // Открытие файла на запись
            pdata = (GDALDataset*)GDALOpen(_fullname_tmp_tiff.toLocal8Bit().data(), GA_Update);
            if (pdata != 0) {
                // Buffer for acoustic data
                // QVector<float> buf;
                // QVector<unsigned char> buf_uchar;
                unsigned int buf_size = get_values_count(_acoustic_channel_id, i);
                std::cout << "buf_size = " << buf_size << '\n';
                float *raw_float_buf = new float[buf_size];
                unsigned char *raw_uchar_buf = new unsigned char[buf_size];
                if (buf_size > 0) {
                    // Read acoustic data from DB
                    // unsigned int buf_size_check = get_values (_acoustic_channel_id, i, buf.data(), buf_size);
                    unsigned int buf_size_check = get_values (_acoustic_channel_id, i, raw_float_buf, buf_size);
                    // for (int j = 0; j < buf_size_check; ++j)
                        // buf_uchar[j] = static_cast<unsigned char>(buf[j] * 255.0);
                    for (int j = 0; j < buf_size_check; ++j)
                        raw_uchar_buf[j] = static_cast<unsigned char>(raw_float_buf[j] * 255.0 * 2);

                    // Write acoustic data to tmp.tif
                    pdata->RasterIO (GF_Write, 0, i, buf_size_check, 1, raw_uchar_buf, buf_size_check, 1, GDT_Byte, 1, NULL, 0, 0, 0);
                    // pdata->RasterIO (GF_Write, 0, i, buf_size_check, 1, raw_buf, buf_size_check, 1, GDT_Float32, 1, NULL, 0, 0, 0);
                    // pdata->RasterIO (GF_Write, i, 0, 1, buf_size_check, buf.data(), 1, buf_size_check, GDT_Float32, 1, NULL, 0, 0, 0);
                    // pdata->RasterIO (GF_Write, i, 0, 1, buf_size_check, buf.data(), 1, buf_size_check, GDT_Byte, 1, NULL, sizeof(unsigned char));
                    // Write data to overviews with corresponding scale
                    delete[]raw_float_buf;
                    delete[]raw_uchar_buf;
                    emit number_worked_lines(i);
                }
            }
            GDALClose(pdata);

            // Pause
            usleep(_time_delay * 1000000);
            std::cout << "Read line, _time_delay = " << _time_delay << '\n';
            // std::this_thread::sleep_for(std::chrono::milliseconds(_time_delay));
        }
    }
}
*/
