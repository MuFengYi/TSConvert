//#include <iostream>
//#include "MxMp4.h"
//using namespace std;
// 
//class MxMp4
//{
//   public:
//      double length;   // 长度
//      double breadth;  // 宽度
//      double height;   // 高度
//      // 成员函数声明
//      double get(void);
//    
//    
//    
//    
//    
//      int writeMp4Header();
//};
//// 成员函数定义
//double MxMp4::get(void)
//{
//    return length * breadth * height;
//}
// 
//int MxMp4::writeMp4Header()
//{
//    AVOutputFormat *ofmt = NULL;
//    int ret = -1, i;
//    // Output
//    ret = avformat_alloc_output_context2(&m_pOutContext, NULL, NULL, m_sMp4OutFileName.toStdString().c_str());
//    if (!m_pOutContext)
//    {
//        printf("Could not create output context\n");
//        char errorbuf[1024] = {0};
//        av_strerror(ret, errorbuf, sizeof(errorbuf));
//        return ret;
//    }
//    ofmt = m_pOutContext->oformat;
//    if (m_sVideoRes.codec != VIDEO_UNKNOWN)
//    {
//        AVCodecID codecId = AV_CODEC_ID_H264;
//        if (m_sVideoRes.codec == E_H265)
//        {
//            codecId = AV_CODEC_ID_H265;
//        }
//        ofmt->video_codec = codecId;
//        AVCodec *pCodec = avcodec_find_encoder(codecId);
//        // x264 不能直接使用avformat_new_stream(xxx,null)分配而来的codec，应该是某些参数未成功初始化
//        AVStream *out_stream = avformat_new_stream(m_pOutContext, pCodec);
//        if (!out_stream)
//        {
//            printf("Failed allocating output stream\n");
//            ret = AVERROR_UNKNOWN;
//            return ret;
//        }
//        videoindex_out = out_stream->index;
//        AVCodecContext *pCodecCtx = out_stream->codec;
//        // pCodecCtx->frame_number = 1;
//        pCodecCtx->codec_id = codecId;
//        pCodecCtx->pix_fmt = (AVPixelFormat)m_pCodecParam->format;
//        pCodecCtx->time_base.num = 1;
//        pCodecCtx->time_base.den = 1000;
//        pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
//        pCodecCtx->width = m_sVideoRes.width;
//        pCodecCtx->height = m_sVideoRes.height;
//        pCodecCtx->codec_tag = 0;
//        pCodecCtx->bit_rate = 0;
//        pCodecCtx->bit_rate_tolerance = 4000000;
//        pCodecCtx->qmin = 2;
//        pCodecCtx->qmax = 31;
//        pCodecCtx->gop_size = 12;
//        pCodecCtx->max_b_frames = 0;
//        if (m_pOutContext->oformat->flags & AVFMT_GLOBALHEADER)
//            pCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
//        AVDictionary *param = 0;
//        if (pCodecCtx->codec_id == AV_CODEC_ID_H264)
//        {
//            av_dict_set(&param, "preset", "slow", 0);
//            av_dict_set(&param, "tune", "zerolatency", 0);
//        }
//        // H.265
//        if (pCodecCtx->codec_id == AV_CODEC_ID_H265)
//        {
//            av_dict_set(&param, "x265-params", "qp=20", 0);
//            av_dict_set(&param, "preset", "ultrafast", 0);
//            av_dict_set(&param, "tune", "zero-latency", 0);
//        }
//        ret = avcodec_open2(pCodecCtx, pCodec, &param);
//        if (ret < 0)
//        {
//            char errbuffer[512];
//            av_strerror(ret, errbuffer, 512);
//            qDebug() << errbuffer;
//            m_pOutContext->streams[0]->codec = nullptr;
//            return -2;
//        }
//        m_pPacket_v = av_packet_alloc();
//    }
// 
// 
//    if (m_sAudioRes.codec == E_ALAW)
//    {
//        ofmt->audio_codec = AV_CODEC_ID_AAC;
// 
//        AVStream *out_stream_a = avformat_new_stream(m_pOutContext, NULL);
//        if (!out_stream_a)
//        {
//            ret = -1;
//            return ret;
//        }
//        audioindex_out = out_stream_a->index;
//        m_pAudioCodecCtx = out_stream_a->codec;
//        m_pAudioCodecCtx->bit_rate = 0;
//        m_pAudioCodecCtx->bit_rate_tolerance = 2000000;
//        m_pAudioCodecCtx->sample_fmt = AV_SAMPLE_FMT_FLTP;
//        m_pAudioCodecCtx->sample_rate = 8000;
//        m_pAudioCodecCtx->channel_layout = AV_CH_LAYOUT_MONO;
//        m_pAudioCodecCtx->channels = av_get_channel_layout_nb_channels(m_pAudioCodecCtx->channel_layout);
//        m_pAudioCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
//        m_pAudioCodecCtx->time_base.num = 1;
//        m_pAudioCodecCtx->time_base.den = 8000;
// 
//        AVCodec *pCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
//        if (m_pOutContext->oformat->flags & AVFMT_GLOBALHEADER)
//            m_pAudioCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
//        ret = avcodec_open2(m_pAudioCodecCtx, pCodec, NULL);
//        if (ret < 0)
//        {
//            printf("Failed to open encoder!\n");
//            return ret;
//        }
//        m_pAudioFrame = av_frame_alloc();
//        m_pAudioFrame->nb_samples = m_pAudioCodecCtx->frame_size;
//        m_pAudioFrame->format = m_pAudioCodecCtx->sample_fmt;
//        m_pAudioFrame->channels = 1;
//        // ret = av_frame_make_writable(m_pAudioFrame);
//        m_nAudioFramSize = av_samples_get_buffer_size(NULL, m_pAudioCodecCtx->channels, m_pAudioCodecCtx->frame_size, m_pAudioCodecCtx->sample_fmt, 1);
//        m_pAudioFrameBuf[0] = (uint8_t *)av_malloc(m_nAudioFramSize);
//        m_pAudioFrameBuf[1] = (uint8_t *)av_malloc(m_nAudioFramSize);
// 
//        avcodec_fill_audio_frame(m_pAudioFrame, m_pAudioCodecCtx->channels, m_pAudioCodecCtx->sample_fmt, (const uint8_t *)m_pAudioFrameBuf[0], m_nAudioFramSize, 1);
//        m_pPacket_a = av_packet_alloc();
//        av_new_packet(m_pPacket_a, m_nAudioFramSize);
// 
//        m_pAudioSwrContext = swr_alloc();
//        av_opt_set_int(m_pAudioSwrContext, "in_channel_layout", AV_CH_LAYOUT_MONO, 0);
//        av_opt_set_int(m_pAudioSwrContext, "out_channel_layout", AV_CH_LAYOUT_MONO, 0);
//        av_opt_set_int(m_pAudioSwrContext, "in_sample_rate", 8000, 0);
//        av_opt_set_int(m_pAudioSwrContext, "out_sample_rate", 8000, 0);
//        av_opt_set_sample_fmt(m_pAudioSwrContext, "in_sample_fmt", AV_SAMPLE_FMT_S16, 0);
//        av_opt_set_sample_fmt(m_pAudioSwrContext, "out_sample_fmt", AV_SAMPLE_FMT_FLTP, 0);
//        swr_init(m_pAudioSwrContext);
//        m_AudioOuts[0] = new uint8_t[m_nAudioFramSize];
//    }
// 
//    printf("==========Output Information==========\n");
//    av_dump_format(m_pOutContext, 0, m_sMp4OutFileName.toStdString().c_str(), 1);
//    printf("======================================\n");
// 
//    // Open output file
//    if (!(ofmt->flags & AVFMT_NOFILE))
//    {
//        ret = avio_open(&m_pOutContext->pb, m_sMp4OutFileName.toStdString().c_str(), AVIO_FLAG_WRITE);
//        if (ret < 0)
//        {
//            printf("Could not open output file '%s'", m_sMp4OutFileName.toStdString().c_str());
//            return ret;
//        }
//    }
//    // Write file header
//    AVDictionary *opt = NULL;
//    // m_pOutContext->streams[0]->codec->time_base.den = m_sCmsFileInfo.media_info.video_info.rate;
//    av_dict_set_int(&opt, "video_track_timescale", 1000, 0);
//    // av_dict_set_int(&opt, "video_track_timescale", m_sCmsFileInfo.media_info.video_info.rate, 0);
//    // avformat_write_header(m_pOutContext, &opt);
//    if ((ret = avformat_write_header(m_pOutContext, &opt)) < 0)
//    {
//        printf("Error occurred when opening output file\n");
//        return ret;
//    }
//    m_bWriteMp4HeaderSuccess = true;
//    return 0;
//}
