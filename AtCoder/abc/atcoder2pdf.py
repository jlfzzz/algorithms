import os
import json
import base64
import time
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager

# ================= 配置区域 (已更新) =================
# 想要爬取的比赛 ID 范围: 400 到 438 (range结束位需要+1)
CONTESTS = range(400, 439)

# 想要爬取的题目: C, D, E, F, G
PROBLEMS = ["c", "d", "e", "f", "g"]

# 保存目录
OUTPUT_DIR = "AtCoder_PDFs_400_438"
# ===================================================


def init_driver():
    """初始化无头 Chrome 浏览器"""
    chrome_options = Options()
    chrome_options.add_argument("--headless")  # 无界面模式
    chrome_options.add_argument("--disable-gpu")
    chrome_options.add_argument("--no-sandbox")
    # 打印时保留背景色（为了代码块的灰色背景）
    chrome_options.add_argument("--print-to-pdf-no-header")

    service = Service(ChromeDriverManager().install())
    driver = webdriver.Chrome(service=service, options=chrome_options)
    return driver


def save_as_pdf(driver, url, output_path):
    print(f"🌍 Loading: {url}")
    driver.get(url)

    # 关键：等待 MathJax 渲染完成
    # 爬取大量题目时，如果网速快可以尝试改为 2 秒以节省时间，但 3 秒最稳
    time.sleep(3)

    # 使用 Chrome DevTools Protocol (CDP) 直接调用打印功能
    pdf_data = driver.execute_cdp_cmd(
        "Page.printToPDF",
        {
            "printBackground": True,  # 保留背景样式
            "marginTop": 0.4,  # 页边距 (英寸)
            "marginBottom": 0.4,
            "marginLeft": 0.4,
            "marginRight": 0.4,
            "paperWidth": 8.27,  # A4 宽度
            "paperHeight": 11.69,  # A4 高度
            "displayHeaderFooter": False,  # 去掉默认的页眉页脚
        },
    )

    with open(output_path, "wb") as f:
        f.write(base64.b64decode(pdf_data["data"]))
    print(f"✅ Saved: {output_path}")


def main():
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    driver = init_driver()

    total_tasks = len(CONTESTS) * len(PROBLEMS)
    current_count = 0

    print(
        f"🚀 开始任务：共 {len(CONTESTS)} 场比赛，每场 {len(PROBLEMS)} 题，预计生成 {total_tasks} 个 PDF。"
    )

    try:
        for contest_id in CONTESTS:
            for pid in PROBLEMS:
                current_count += 1

                # 构造 URL
                url = f"https://atcoder.jp/contests/abc{contest_id}/tasks/abc{contest_id}_{pid}"
                filename = f"ABC{contest_id}_{pid.upper()}.pdf"
                filepath = os.path.join(OUTPUT_DIR, filename)

                # 简单的进度提示
                print(
                    f"[{current_count}/{total_tasks}] Processing ABC{contest_id} Problem {pid.upper()}..."
                )

                try:
                    save_as_pdf(driver, url, filepath)
                except Exception as e:
                    print(f"❌ Error processing {filename} (可能是该题不存在): {e}")

    finally:
        driver.quit()
        print(f"\n🎉 所有任务完成！文件已保存在文件夹: {OUTPUT_DIR}")


if __name__ == "__main__":
    main()
