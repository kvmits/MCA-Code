from copy import deepcopy
from pathlib import Path
import re

from docx import Document
from docx.enum.text import WD_ALIGN_PARAGRAPH, WD_BREAK, WD_TAB_ALIGNMENT
from docx.oxml import OxmlElement
from docx.oxml.ns import qn
from docx.shared import Inches, Pt


PYTHON_DIR = Path(__file__).parent.parent
RECORD_DIR = Path(__file__).parent
FONT_NAME = "Times New Roman"
FOOTER_LEFT = "Dept. of Computer Applications"
FOOTER_RIGHT = "Muthoot Institute of Technology & Science(Autonomous)"
OUTPUT_PATTERN = re.compile(r"'''\s*Output:\s*\n(.*?)\n'''\s*$", re.DOTALL)
PROMPT_PATTERN = re.compile(r"^\d+(?:\.\d+)?\.")


def set_page_layout(document, reference):
    reference_section = Document(reference).sections[0]
    section = document.sections[0]
    section.page_width = reference_section.page_width
    section.page_height = reference_section.page_height
    section.top_margin = reference_section.top_margin
    section.bottom_margin = reference_section.bottom_margin
    section.left_margin = reference_section.left_margin
    section.right_margin = reference_section.right_margin


def clear_body(document):
    body = document.element.body
    section_properties = body.sectPr
    for child in list(body):
        if child is not section_properties:
            body.remove(child)


def format_footer(document):
    section = document.sections[0]
    paragraph = section.footer.paragraphs[0]
    paragraph.clear()
    paragraph.alignment = WD_ALIGN_PARAGRAPH.LEFT
    content_width = section.page_width - section.left_margin - section.right_margin
    paragraph.paragraph_format.tab_stops.clear_all()
    paragraph.paragraph_format.tab_stops.add_tab_stop(int(content_width * 0.35), WD_TAB_ALIGNMENT.CENTER)
    paragraph.paragraph_format.tab_stops.add_tab_stop(content_width, WD_TAB_ALIGNMENT.RIGHT)

    def add_footer_run(text=None):
        run = paragraph.add_run(text or "")
        run.font.name = "Roboto"
        run.font.size = Pt(9.5)
        run.bold = True
        return run

    add_footer_run(FOOTER_LEFT)
    add_footer_run().add_tab()
    field_run = add_footer_run()
    begin = OxmlElement("w:fldChar")
    begin.set(qn("w:fldCharType"), "begin")
    instruction = OxmlElement("w:instrText")
    instruction.set(qn("xml:space"), "preserve")
    instruction.text = " PAGE "
    separate = OxmlElement("w:fldChar")
    separate.set(qn("w:fldCharType"), "separate")
    result = OxmlElement("w:t")
    result.text = "1"
    end = OxmlElement("w:fldChar")
    end.set(qn("w:fldCharType"), "end")
    field_run._r.extend((begin, instruction, separate, result, end))
    add_footer_run().add_tab()
    add_footer_run(FOOTER_RIGHT)


def add_text_paragraph(document, text, size, bold=False):
    paragraph = document.add_paragraph()
    run = paragraph.add_run(text)
    run.bold = bold
    run.font.name = FONT_NAME
    run.font.size = Pt(size)
    return paragraph


def add_program_page_breaks(document):
    first_program = True
    for paragraph in document.paragraphs:
        if paragraph.text.startswith("COURSE OUTCOME"):
            first_program = True
        elif PROMPT_PATTERN.match(paragraph.text) and paragraph.runs and paragraph.runs[0].bold:
            if not first_program:
                paragraph.paragraph_format.page_break_before = True
            first_program = False


def extract_program(source_path):
    source = source_path.read_text(encoding="utf-8")
    lines = source.splitlines()
    prompt_lines = []
    first_code_line = 0

    for index, line in enumerate(lines):
        if line.lstrip().startswith("#"):
            prompt_lines.append(line.lstrip()[1:].strip())
            first_code_line = index + 1
        elif not line.strip() and not prompt_lines:
            first_code_line = index + 1
        else:
            break

    output_match = OUTPUT_PATTERN.search(source)
    if not prompt_lines or output_match is None:
        raise ValueError(f"Could not parse prompt or output in {source_path.name}")

    prompt = " ".join(line for line in prompt_lines if line)
    program = "\n".join(lines[first_code_line:]).split("'''", 1)[0].strip()
    output = output_match.group(1).strip("\n")
    return prompt, program, output


def build_outcome(outcome):
    source_dir = PYTHON_DIR / f"CO{outcome}"
    source_files = sorted(source_dir.glob(f"CO{outcome}_*.py"), key=lambda path: int(path.stem.split("_")[1]))
    reference = RECORD_DIR / "CO1 Python Record.docx"
    document = Document(reference)
    clear_body(document)
    format_footer(document)
    heading = add_text_paragraph(document, f"COURSE OUTCOME {outcome}", 12, True)
    heading.alignment = WD_ALIGN_PARAGRAPH.CENTER

    for source_path in source_files:
        prompt, program, output = extract_program(source_path)
        add_text_paragraph(document, prompt, 13, True)
        add_text_paragraph(document, "Program:", 13, True)
        for line in program.splitlines():
            add_text_paragraph(document, line or " ", 11.5)
        add_text_paragraph(document, "", 11.5)
        add_text_paragraph(document, "Output:", 13, True)
        for line in output.splitlines():
            add_text_paragraph(document, line or " ", 11.5)
        add_text_paragraph(document, "", 11.5)

    add_program_page_breaks(document)
    destination = RECORD_DIR / f"CO{outcome} Python Record.docx"
    document.save(destination)
    return destination


def build_combined(outcome_documents):
    document_paths = [
        RECORD_DIR / "CO1 Python Record.docx",
        RECORD_DIR / "CO2 Python Record.docx",
        *outcome_documents,
    ]
    combined = Document(document_paths[0])
    clear_body(combined)
    format_footer(combined)
    body = combined.element.body
    section_properties = body.sectPr

    for index, source_path in enumerate(document_paths):
        source = Document(source_path)
        if index:
            page_break = combined.add_paragraph()
            page_break.add_run().add_break(WD_BREAK.PAGE)
        for child in source.element.body:
            if child.tag.endswith("}sectPr"):
                continue
            body.append(deepcopy(child))

    body.append(section_properties)
    for paragraph in combined.paragraphs:
        if paragraph.text.startswith("COURSE OUTCOME"):
            paragraph.alignment = WD_ALIGN_PARAGRAPH.CENTER
    add_program_page_breaks(combined)
    combined.save(RECORD_DIR / "Python Record.docx")


if __name__ == "__main__":
    for outcome in (1, 2):
        source_record = RECORD_DIR / f"CO{outcome} Python Record.docx"
        source_document = Document(source_record)
        add_program_page_breaks(source_document)
        source_document.save(source_record)
    outcome_documents = [build_outcome(outcome) for outcome in (3, 4)]
    build_combined(outcome_documents)