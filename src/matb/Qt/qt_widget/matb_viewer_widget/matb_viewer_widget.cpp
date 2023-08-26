#include "matb_viewer_widget.hpp"

namespace matb
{
    MatbViewerWidget::MatbViewerWidget(yarp::os::ResourceFinder& _rf)
    {
        /* subscriber */
        resman_image_subscriber_buffered_port_.useCallback(resman_image_subscriber_);
        resman_image_subscriber_buffered_port_.setReplier(resman_image_subscriber_);
        resman_image_subscriber_buffered_port_.open("/" + _rf.find("name").asString() + "/resman_task/image/sub");
        resman_status_image_subscriber_buffered_port_.useCallback(resman_status_image_subscriber_);
        resman_status_image_subscriber_buffered_port_.setReplier(resman_status_image_subscriber_);
        resman_status_image_subscriber_buffered_port_.open("/" + _rf.find("name").asString() + "/pump_status/image/sub");
        sysmon_image_subscriber_buffered_port_.useCallback(sysmon_image_subscriber_);
        sysmon_image_subscriber_buffered_port_.setReplier(sysmon_image_subscriber_);
        sysmon_image_subscriber_buffered_port_.open("/" + _rf.find("name").asString() + "/sysmon_task/image/sub");
        tracking_image_subscriber_buffered_port_.useCallback(tracking_image_subscriber_);
        tracking_image_subscriber_buffered_port_.setReplier(tracking_image_subscriber_);
        tracking_image_subscriber_buffered_port_.open("/" + _rf.find("name").asString() + "/tracking_task/image/sub");
        comm_image_subscriber_buffered_port_.useCallback(comm_image_subscriber_);
        comm_image_subscriber_buffered_port_.setReplier(comm_image_subscriber_);
        comm_image_subscriber_buffered_port_.open("/" + _rf.find("name").asString() + "/communications_task/image/sub");
        sched_image_subscriber_buffered_port_.useCallback(sched_image_subscriber_);
        sched_image_subscriber_buffered_port_.setReplier(sched_image_subscriber_);
        sched_image_subscriber_buffered_port_.open("/" + _rf.find("name").asString() + "/scheduling_display/image/sub");

        /* pub */
        key_press_event_publisher_buffered_port_.open("/" + _rf.find("name").asString() + "/key_press_event/pub");
        key_release_event_publisher_buffered_port_.open("/" + _rf.find("name").asString() + "/key_release_event/pub");
        width_ = _rf.find("width").asInt32();
        height_ = _rf.find("height").asInt32();
        init();
    }

    MatbViewerWidget::~MatbViewerWidget()
    {
        close();
    }

    void MatbViewerWidget::closeEvent(QCloseEvent* _event)
    {
        close();
    }

    void MatbViewerWidget::close()
    {
        /* sub  */
        resman_image_subscriber_buffered_port_.close();
        resman_status_image_subscriber_buffered_port_.close();
        sysmon_image_subscriber_buffered_port_.close();
        tracking_image_subscriber_buffered_port_.close();
        comm_image_subscriber_buffered_port_.close();
        sched_image_subscriber_buffered_port_.close();
        /* pub */
        key_press_event_publisher_buffered_port_.close();
        key_release_event_publisher_buffered_port_.close();

        std::cout << " Closing MatbViewerWidget ports " << std::endl;
    }

    void MatbViewerWidget::leaveEvent(QEvent* event)
    {

    }

    void MatbViewerWidget::init()
    {
        q_basic_timer_.start(10, this);
        sysmon_label_.resize(300, 300);
        tracking_label_.resize(300, 300);
        sched_label_.resize(300, 300);
        comm_label_.resize(300, 300);
        resman_status_label_.resize(300, 300);
        resman_label_.resize(300, 300);
        this->setLayout(&vbox_layout_);
        vbox_layout_.addLayout(&above_layout_);
        vbox_layout_.addLayout(&below_layout_);
        vbox_layout_.setAlignment(Qt::AlignCenter);
        above_layout_.addWidget(&sysmon_label_);
        above_layout_.addWidget(&tracking_label_);
        above_layout_.addWidget(&sched_label_);
        above_layout_.setAlignment(Qt::AlignCenter);
        below_layout_.addWidget(&comm_label_);
        below_layout_.addWidget(&resman_label_);
        below_layout_.addWidget(&resman_status_label_);
        below_layout_.setAlignment(Qt::AlignCenter);
    }


    void MatbViewerWidget::keyPressEvent(QKeyEvent* _event)
    {
        yarp::rosmsg::matb_msgs::QKey key_press_msg;
        key_press_msg.timestamp = _event->timestamp();
        key_press_msg.text = _event->text().toStdString();
        key_press_msg.count = _event->count();
        key_press_msg.key = _event->key();
        key_press_msg.type = _event->type();
        key_press_msg.modifiers = _event->modifiers();
        key_press_msg.native_modifiers = _event->nativeModifiers();
        key_press_msg.native_scan_code = _event->nativeScanCode();
        key_press_msg.native_virtual_key = _event->nativeVirtualKey();
        key_press_msg.is_auto_repeat = _event->isAutoRepeat();
        key_press_msg.is_accepted = _event->isAccepted();
        key_press_msg.spontaneous = _event->spontaneous();
        key_press_event_publisher_buffered_port_.prepare() = key_press_msg;
        key_press_event_publisher_buffered_port_.write();
        std::cout << "text: " << key_press_msg.text << std::endl;
        std::cout << "count: " << key_press_msg.count << std::endl;
        std::cout << "key: " << key_press_msg.key << std::endl;
        std::cout << "type: " << key_press_msg.type << std::endl;
        std::cout << "modifiers: " << key_press_msg.modifiers << std::endl;
        std::cout << "native_modifiers: " << key_press_msg.native_modifiers << std::endl;
        std::cout << "native_scan_code: " << key_press_msg.native_scan_code << std::endl;
        std::cout << "native_virtual_key: " << key_press_msg.native_virtual_key << std::endl;
        std::cout << "is_auto_repeat: " << key_press_msg.is_auto_repeat << std::endl;
        std::cout << "is_accepted: " << key_press_msg.is_accepted << std::endl;
        std::cout << "spontaneous: " << key_press_msg.spontaneous << std::endl;
        std::cout << std::endl;
    }

    void MatbViewerWidget::keyReleaseEvent(QKeyEvent* _event)
    {
        yarp::rosmsg::matb_msgs::QKey key_release_msg;
        key_release_msg.timestamp = _event->timestamp();
        key_release_msg.text = _event->text().toStdString();
        key_release_msg.count = _event->count();
        key_release_msg.key = _event->key();
        key_release_msg.type = _event->type();
        key_release_msg.modifiers = _event->modifiers();
        key_release_msg.native_modifiers = _event->nativeModifiers();
        key_release_msg.native_scan_code = _event->nativeScanCode();
        key_release_msg.native_virtual_key = _event->nativeVirtualKey();
        key_release_msg.is_auto_repeat = _event->isAutoRepeat();
        key_release_msg.is_accepted = _event->isAccepted();
        key_release_msg.spontaneous = _event->spontaneous();
        key_release_event_publisher_buffered_port_.prepare() = key_release_msg;
        key_release_event_publisher_buffered_port_.write();
    }

    void MatbViewerWidget::mouseDoubleClickEvent(QMouseEvent* _event)
    {
    }

    void MatbViewerWidget::mouseMoveEvent(QMouseEvent* _event)
    {
    }

    void MatbViewerWidget::mousePressEvent(QMouseEvent* _event)
    {
    }

    void MatbViewerWidget::paintEvent(QPaintEvent* _event)
    {
    }

    void MatbViewerWidget::timerEvent(QTimerEvent* _event)
    {
        int width = 500;
        int height = 500;
        QImage white_image(width, height, QImage::Format_RGB32);
        white_image.fill(Qt::white);

        // For resman_image
        auto resman_yarp_image = resman_image_subscriber_.bottle();
        if(resman_yarp_image.width() <= 0||resman_yarp_image.height() <= 0)
        {
            std::cerr << "Received YARP image for resman is not valid!" << std::endl;
            resman_label_.setPixmap(QPixmap::fromImage(white_image).scaled(width_, height_));
        }
        else
        {
            auto resman_cv_image = yarp::cv::toCvMat(resman_yarp_image);
            if(!resman_cv_image.empty())
            {
                cvtColor(resman_cv_image, resman_cv_image, CV_BGR2RGB);
                QImage resman_q_image = QImage((uchar*) resman_cv_image.data, resman_cv_image.cols, resman_cv_image.rows, resman_cv_image.step, QImage::Format_RGB888);
                resman_label_.setPixmap(QPixmap::fromImage(resman_q_image).scaled(width_, height_));
            }
        }

        // For resman_status_image
        auto resman_status_yarp_image = resman_status_image_subscriber_.bottle();
        if(resman_status_yarp_image.width() <= 0||resman_status_yarp_image.height() <= 0)
        {
            std::cerr << "Received YARP image for resman_status is not valid!" << std::endl;
            resman_status_label_.setPixmap(QPixmap::fromImage(white_image).scaled(width_, height_));
        }
        else
        {
            auto resman_status_cv_image = yarp::cv::toCvMat(resman_status_yarp_image);
            if(!resman_status_cv_image.empty())
            {
                cvtColor(resman_status_cv_image, resman_status_cv_image, CV_BGR2RGB);
                QImage resman_status_q_image = QImage((uchar*) resman_status_cv_image.data, resman_status_cv_image.cols, resman_status_cv_image.rows, resman_status_cv_image.step, QImage::Format_RGB888);
                resman_status_label_.setPixmap(QPixmap::fromImage(resman_status_q_image).scaled(width_, height_));
            }
        }

        // For sysmon_image
        auto sysmon_yarp_image = sysmon_image_subscriber_.bottle();
        if(sysmon_yarp_image.width() <= 0||sysmon_yarp_image.height() <= 0)
        {
            std::cerr << "Received YARP image for sysmon is not valid!" << std::endl;
            sysmon_label_.setPixmap(QPixmap::fromImage(white_image).scaled(width_, height_));
        }
        else
        {
            auto sysmon_cv_image = yarp::cv::toCvMat(sysmon_yarp_image);
            if(!sysmon_cv_image.empty())
            {
                cvtColor(sysmon_cv_image, sysmon_cv_image, CV_BGR2RGB);
                QImage sysmon_q_image = QImage((uchar*) sysmon_cv_image.data, sysmon_cv_image.cols, sysmon_cv_image.rows, sysmon_cv_image.step, QImage::Format_RGB888);
                sysmon_label_.setPixmap(QPixmap::fromImage(sysmon_q_image).scaled(width_, height_));
            }
        }

        // For tracking_image
        auto tracking_yarp_image = tracking_image_subscriber_.bottle();
        if(tracking_yarp_image.width() <= 0||tracking_yarp_image.height() <= 0)
        {
            std::cerr << "Received YARP image for tracking is not valid!" << std::endl;
            tracking_label_.setPixmap(QPixmap::fromImage(white_image).scaled(width_, height_));
        }
        else
        {
            auto tracking_cv_image = yarp::cv::toCvMat(tracking_yarp_image);
            if(!tracking_cv_image.empty())
            {
                cvtColor(tracking_cv_image, tracking_cv_image, CV_BGR2RGB);
                QImage tracking_q_image = QImage((uchar*) tracking_cv_image.data, tracking_cv_image.cols, tracking_cv_image.rows, tracking_cv_image.step, QImage::Format_RGB888);
                tracking_label_.setPixmap(QPixmap::fromImage(tracking_q_image).scaled(width_, height_));
            }
        }

        // For comm_image
        auto comm_yarp_image = comm_image_subscriber_.bottle();
        if(comm_yarp_image.width() <= 0||comm_yarp_image.height() <= 0)
        {
            std::cerr << "Received YARP image for comm is not valid!" << std::endl;
            comm_label_.setPixmap(QPixmap::fromImage(white_image).scaled(width_, height_));
        }
        else
        {
            auto comm_cv_image = yarp::cv::toCvMat(comm_yarp_image);
            if(!comm_cv_image.empty())
            {
                cvtColor(comm_cv_image, comm_cv_image, CV_BGR2RGB);
                QImage comm_q_image = QImage((uchar*) comm_cv_image.data, comm_cv_image.cols, comm_cv_image.rows, comm_cv_image.step, QImage::Format_RGB888);
                comm_label_.setPixmap(QPixmap::fromImage(comm_q_image).scaled(width_, height_));
            }
        }

        // For sched_image
        auto sched_yarp_image = sched_image_subscriber_.bottle();
        if(sched_yarp_image.width() <= 0||sched_yarp_image.height() <= 0)
        {
            std::cerr << "Received YARP image for sched is not valid!" << std::endl;
            sched_label_.setPixmap(QPixmap::fromImage(white_image).scaled(width_, height_));
        }
        else
        {
            auto sched_cv_image = yarp::cv::toCvMat(sched_yarp_image);
            if(!sched_cv_image.empty())
            {
                cvtColor(sched_cv_image, sched_cv_image, CV_BGR2RGB);
                QImage sched_q_image = QImage((uchar*) sched_cv_image.data, sched_cv_image.cols, sched_cv_image.rows, sched_cv_image.step, QImage::Format_RGB888);
                sched_label_.setPixmap(QPixmap::fromImage(sched_q_image).scaled(width_, height_));
            }
        }
    }


    void MatbViewerWidget::wheelEvent(QWheelEvent* _event)
    {
    }


};












